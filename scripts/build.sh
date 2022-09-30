#!/usr/bin/env bash

## Important directories.
declare -r SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)";
declare -r ROOT_DIR="$(dirname "$SCRIPT_DIR")";

declare -r BUILD_DIR="${ROOT_DIR}/build"; ## Build artifacts
declare -r DIST_DIR="${ROOT_DIR}/dist";   ## Final release artifacts.

declare -r LIBS_ROOT_DIR="${ROOT_DIR}/lib/Cooper";
declare -r GAME_ROOT_DIR="${ROOT_DIR}/game";
declare -r ASSETS_DIR="${ROOT_DIR}/assets";

declare CREATE_DIST_PACKAGE="";  ## Should create release package?

declare -r GAME_NAME="kaboom";
declare -r GAME_VERSION=$(cat "${ROOT_DIR}/game/version" | tr -d "\""); ## without any quotes...

declare GAME_BUILD_TYPE="Release"; ## Passed to Cmake.
declare GAME_BUILD_TARGET="pc";    ## Passed to Cmake.

declare PLATFORM_NAME="$(uname)"; ## @todo: check on mac os...


##
## Parse the command line.
##
function show_help()
{
    echo "invalid arg: ($1)";

    echo "Usage:";
    echo "   --release  --debug -> Build Modes";
    echo "   --pc       --web   -> Build Targets";
    echo "   --package          -> Make distribution zip?";
    exit 1;
}


while true; do
    case "$1" in
        "--release" ) GAME_BUILD_TYPE="Release";  ;;
        "--debug"   ) GAME_BUILD_TYPE="Debug";    ;;
        "--pc"      ) GAME_BUILD_TARGET="pc";     ;;
        "--web"     ) GAME_BUILD_TARGET="web";    ;;
        "--package" ) CREATE_DIST_PACKAGE="true"; ;;
        *) show_help "$1";                        ;;
    esac;
    shift;
    if [ $# -eq 0 ]; then
        break;
    fi;
done;

echo "   GAME_NAME:           (${GAME_NAME})";
echo "   GAME_ROOT_DIR:       (${GAME_ROOT_DIR})";
echo "   GAME_BUILD_TYPE:     (${GAME_BUILD_TYPE})";
echo "   GAME_BUILD_TARGET:   (${GAME_BUILD_TARGET})";
echo "   CREATE_DIST_PACKAGE: (${CREATE_DIST_PACKAGE})";

##
## Build the game.
##

function build_game()
{
    local target_platform="$1";

    echo "Building game for platform: (${target_platform})";

    mkdir -p "${BUILD_DIR}";
    pushd "${BUILD_DIR}";
        cmake                                                  \
            -DGAME_NAME="${GAME_NAME}"                         \
            -DGAME_ROOT_DIR="${ROOT_DIR}"                      \
            -DGAME_BUILD_TYPE="${GAME_BUILD_TYPE}"             \
                                                               \
            -DCMAKE_MODULE_PATH="${ROOT_DIR}/cmake/cmake_find" \
                                                               \
            -S"${ROOT_DIR}/game"                               \
        ;

        cmake                             \
            --build .                     \
            --config "${GAME_BUILD_TYPE}" \
        ;
    popd;
}


test "${GAME_BUILD_TARGET}" == "pc"   && build_game "pc";
# test "${GAME_BUILD_TARGET}" == "web"  && build_game "web";


##
## Package if needed...
##

# if [ -n "$CREATE_DIST_PACKAGE" ]; then
    # GAME_DIST_DIR="${DIST_DIR}/cosmic-intruders-${GAME_VERSION}-${PLATFORM_NAME}-${BUILD_TYPE}";
    # GAME_ZIP_FILENAME="${DIST_DIR}/cosmic-intruders-${GAME_VERSION}-${PLATFORM_NAME}.zip";
#
    # mkdir -p "${GAME_DIST_DIR}"                          \
        # && cd  "${GAME_DIST_DIR}"                        \
        # && cp     "${ROOT_DIR}/build/cosmic-intruders" . \
        # && cp  -R "${ROOT_DIR}/assets"                 . \
        # && zip -r "${GAME_ZIP_FILENAME}"               . \
    # ;
#
    # echo "Generated zip at: $GAME_ZIP_FILENAME";
# fi;
#
