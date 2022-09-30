##~---------------------------------------------------------------------------##
##                        _      _                 _   _                      ##
##                    ___| |_ __| |_ __ ___   __ _| |_| |_                    ##
##                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   ##
##                   \__ \ || (_| | | | | | | (_| | |_| |_                    ##
##                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   ##
##                                                                            ##
##  File      : CMakeLists.txt                                                ##
##  Project   : kaboom                                                        ##
##  Date      : Mar 15, 2020                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : stdmatt <stdmatt@pixelwizards.io>                             ##
##  Copyright : stdmatt 2020                                                  ##
##                                                                            ##
##  Description :                                                             ##
##                                                                            ##
##---------------------------------------------------------------------------~##

cmake_minimum_required(VERSION 3.5)
project(${GAME_NAME})

##----------------------------------------------------------------------------##
## Compiler Definitions                                                       ##
##----------------------------------------------------------------------------##
set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_BUILD_TYPE Release)
if(NOT GAME_BUILD_TYPE)
    message("[Setting build type to Debug]")
    set(CMAKE_BUILD_TYPE Debug)
endif()

IF(${CMAKE_BUILD_TYPE} MATCHES "Release")
    message("[Setting debug additional defines]")
    add_definitions(-DCOREGAME_RELEASE)
    add_definitions(-DLORE_RELEASE)
ENDIF()

message("[Build type is configure to: ${CMAKE_BUILD_TYPE}]")

find_package(SDL2       REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf   REQUIRED)
find_package(SDL2_mixer REQUIRED)


##----------------------------------------------------------------------------##
## Include Directories                                                        ##
##----------------------------------------------------------------------------##
include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
)

include_directories(
    ${GAME_ROOT_DIR}/lib/Lore
    ${GAME_ROOT_DIR}/lib/Lore/lib/CoreClock/include
    ${GAME_ROOT_DIR}/lib/Lore/lib/CoreGame/include
    ${GAME_ROOT_DIR}/lib/Lore/lib/CoreRandom/include

    ${GAME_ROOT_DIR}/game/include
)


##----------------------------------------------------------------------------##
## Source Files                                                               ##
##----------------------------------------------------------------------------##
file(GLOB_RECURSE LIB_SRC  ${GAME_ROOT_DIR}/lib/*.cpp)
file(GLOB_RECURSE GAME_SRC ${GAME_ROOT_DIR}/game/*.cpp)

##----------------------------------------------------------------------------##
## Executable Definitions                                                     ##
##----------------------------------------------------------------------------##
add_executable(${GAME_NAME} ${LIB_SRC} ${GAME_SRC})

target_include_directories(${GAME_NAME} PUBLIC ${SDL2_INCLUDE_DIR}        )
target_include_directories(${GAME_NAME} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS} )
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_MIXER_INCLUDE_DIRS} )
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_TTF_INCLUDE_DIRS}   )

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_LIBRARY}        )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_MIXER_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_TTF_LIBRARIES}  )
