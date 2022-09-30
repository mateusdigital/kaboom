#!/usr/bin/env bash
##----------------------------------------------------------------------------##
##                   .                                           .   _        ##
##    , _ , _    ___ /_    ___ ,   .  ____       ___   ___ .___ _/_  /        ##
##    |' `|' `. /   `|   .'   `|   | (    .---'.'   ` /   `/   \ |   |,---.   ##
##    |   |   ||    ||   |----'|   | `--.      |----'|    ||   ' |   |'   `   ##
##    /   '   /`.__/|\__/`.___,`._/|\___.'     `.___,`.__/|/     \__//    |   ##
##                        https://mateus.earth                                ##
##                                                                            ##
##  File      : build.sh                                                      ##
##  Project   : Kaboom                                                        ##
##  Date      : 22-09-30                                                      ##
##  License   : GPLv3                                                         ##
##  Author    : mateus-earth <matt@cosmicpig.digital>                         ##
##  Copyright : mateus-earth - 2022                                           ##
##                                                                            ##
##  Description:                                                              ##
##                                                                            ##
##----------------------------------------------------------------------------##

## Important directories.
declare -r SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)";
declare -r ROOT_DIR="$(dirname "$SCRIPT_DIR")";

declare -r BUILD_ROOT="${ROOT_DIR}/build"; ## Build artifacts.
declare -r DIST_ROOT="${ROOT_DIR}/dist";   ## Final release artifacts.

declare -r LIBS_ROOT_DIR="${ROOT_DIR}/lib/Cooper";
declare -r GAME_ROOT_DIR="${ROOT_DIR}/game";
declare -r ASSETS_DIR="${ROOT_DIR}/assets";

declare CREATE_DIST_PACKAGE="true";  ## Should create release package?

declare -r GAME_NAME="kaboom";
declare -r GAME_VERSION="1.4.0";

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
        *) test -n "$1" && show_help "$1";        ;;
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

VERSION_HEADER="${ROOT_DIR}/game/include/Version.h";
echo -e "#pragma once\n#define GAME_VERSION \"${GAME_VERSION}\"" > "${VERSION_HEADER}";

declare -r BUILD_DIR="${BUILD_ROOT}/${GAME_BUILD_TARGET}/${GAME_BUILD_TYPE}";

echo "Building game for platform: (${GAME_BUILD_TARGET})";

mkdir -p "${BUILD_DIR}";
pushd "${BUILD_DIR}" || exit 1;
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


##
## Package if needed...
##

if [ -n "${CREATE_DIST_PACKAGE}" ]; then
    declare -r full_filename="${GAME_NAME}-${GAME_VERSION}-${PLATFORM_NAME}-${GAME_BUILD_TYPE}";
    declare -r game_dist_dir="${DIST_ROOT}/${full_filename}";
    declare -r game_zip_filename="${DIST_ROOT}/${full_filename}.zip";

    echo "Creating the distribution file...";

    mkdir -p "${game_dist_dir}";
    pushd "${game_dist_dir}" || exit 1;
        cp     "${BUILD_DIR}/${GAME_NAME}" . ;
        cp  -R "${ROOT_DIR}/assets"        . ;
        zip -r "${game_zip_filename}"      . ;
    popd;

    echo "Generated zip at: ${game_zip_filename}";
fi;
