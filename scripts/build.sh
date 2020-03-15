#!/usr/bin/env bash

##----------------------------------------------------------------------------##
## Imports                                                                    ##
##----------------------------------------------------------------------------##
source /usr/local/src/stdmatt/shellscript_utils/main.sh

##----------------------------------------------------------------------------##
## Constants                                                                  ##
##----------------------------------------------------------------------------##
PROJECT_NAME="kaboom";


##----------------------------------------------------------------------------##
## Vars                                                                       ##
##----------------------------------------------------------------------------##
## Dirs
SCRIPT_DIR="$(pw_get_script_dir)";
PROJECT_ROOT=$(pw_abspath "$SCRIPT_DIR/..");
BUILD_DIR=$(pw_abspath "$PROJECT_ROOT/build");
DIST_DIR=$(pw_abspath "$PROJECT_ROOT/dist");

## Info
MODE="debug";
PLATFORM="desktop";
PLATFORM_BUILD_SCRIPT="";
PROJECT_VERSION="$(bump-the-version     \
    "${PROJECT_ROOT}/include/Version.h" \
    "#define GAME_VERSION"              \
    "show")";

DIST_FILES="                   \
    ${BUILD_DIR}/$PROJECT_NAME \
    ${PROJECT_ROOT}/assets/    \
";


##----------------------------------------------------------------------------##
## Functions                                                                  ##
##----------------------------------------------------------------------------##
##------------------------------------------------------------------------------
show_help()
{
    cat << END_TEXT
Usage:
    build.sh
      --help                        - Show this info.
      --clean                       - Cleans the build files.
      --mode <*debug | release>     - Compile mode.
      --dist                        - Generate the release zip file.

    Options marked with * is assumed to be the default if none is given.
END_TEXT

    exit $1
}


##------------------------------------------------------------------------------
clean()
{
    pw_func_log "Cleaning files...";

    pw_func_log "   Build path: $(pw_FC $BUILD_DIR)";
    rm -rf "${BUILD_DIR}";

    pw_func_log "   Dist path: $(pw_FC $DIST_DIR)";
    rm -rf "${DIST_DIR}"
}


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
cd "${PROJECT_ROOT}";

##
## Parse the command line arguments.
if [ -n "$(pw_getopt_exists "--clean" "$@")" ]; then
    clean;
    exit 0;
fi;

##
## Build ;D
echo "Bulding (${PROJECT_NAME})";
echo "Build Script directory : $(pw_FC $SCRIPT_DIR     )";
echo "Build directory        : $(pw_FC $BUILD_DIR      )";
echo "Dist  directory        : $(pw_FC $DIST_DIR       )";
echo "Compile mode           : $(pw_FC $MODE           )";
echo "Current version        : $(pw_FC $PROJECT_VERSION)";
echo "";

mkdir -p "$BUILD_DIR";

export PROJECT_ROOT="$PROJECT_ROOT";
export PROJECT_NAME="$PROJECT_NAME";
cmake "${SCRIPT_DIR}/CMakeLists.txt" -B "${BUILD_DIR}";
cd ${BUILD_DIR}
    make;
cd -;

##
## Create the distribution file.
if [ -n "$(pw_getopt_exists "--dist" "$@")" ]; then
    PLATFORM=$(pw_os_get_simple_name);
    echo "Packaging (${PROJECT_NAME}) version: (${PROJECT_VERSION}) for platform: (${PLATFORM})";

    PACKAGE_NAME="${PROJECT_NAME}_${PLATFORM}_${PROJECT_VERSION}";
    PACKAGE_DIR="${DIST_DIR}/${PACKAGE_NAME}";

    ## Clean the directory.
    rm    -rf "${PACKAGE_DIR}";
    mkdir -p  "${PACKAGE_DIR}";

    ## Copy the files to the directory.
    for ITEM in $DIST_FILES; do
        cp -R "$ITEM" "${PACKAGE_DIR}";
    done;

    cd "${DIST_DIR}"
    zip -r "${PACKAGE_NAME}.zip" "./${PACKAGE_NAME}";
    cd -
fi;
