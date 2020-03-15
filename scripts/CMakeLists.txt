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

## External Vars...
## @TODO(stdmatt): Add  an output saying that we need to export this vars...
set(PROJECT_NAME $ENV{PROJECT_NAME})
set(PROJECT_ROOT $ENV{PROJECT_ROOT})

cmake_minimum_required(VERSION 3.5)
project(${PROJECT_NAME})


##----------------------------------------------------------------------------##
## Compiler Definitions                                                       ##
##----------------------------------------------------------------------------##
set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if(NOT CMAKE_BUILD_TYPE)
    message("[Setting build type to Debug]")
    set(CMAKE_BUILD_TYPE Debug)
endif()

IF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    message("[Setting debug additional defines]")
    add_definitions(-DCOREGAME_RELEASE)
    add_definitions(-DLORE_RELEASE)
ENDIF()

message("[Build type is configure to: ${CMAKE_BUILD_TYPE}]")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_find")
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
    ${PROJECT_ROOT}/lib/Lore
    ${PROJECT_ROOT}/lib/Lore/lib/CoreClock/include
    ${PROJECT_ROOT}/lib/Lore/lib/CoreGame/include
    ${PROJECT_ROOT}/lib/Lore/lib/CoreRandom/include
    ${PROJECT_ROOT}/include
)


##----------------------------------------------------------------------------##
## Source Files                                                               ##
##----------------------------------------------------------------------------##
set(SOURCE_FILES
    ${PROJECT_ROOT}/lib/Lore/lib/CoreClock/src/Clock.cpp
    ${PROJECT_ROOT}/lib/Lore/lib/CoreGame/src/Log.cpp
    ${PROJECT_ROOT}/lib/Lore/lib/CoreGame/src/Status.cpp
    ${PROJECT_ROOT}/lib/Lore/lib/CoreGame/src/GameCore_Macros.cpp
    ${PROJECT_ROOT}/lib/Lore/lib/CoreGame/src/StringUtils.cpp
    ${PROJECT_ROOT}/lib/Lore/lib/CoreRandom/src/Random.cpp
    ${PROJECT_ROOT}/lib/Lore/src/InputManager.cpp
    ${PROJECT_ROOT}/lib/Lore/src/Sprite.cpp
    ${PROJECT_ROOT}/lib/Lore/src/SDLHelpers.cpp
    ${PROJECT_ROOT}/lib/Lore/src/Rectangle.cpp
    ${PROJECT_ROOT}/lib/Lore/src/Font.cpp
    ${PROJECT_ROOT}/lib/Lore/src/WindowManager.cpp
    ${PROJECT_ROOT}/lib/Lore/src/Text.cpp
    ${PROJECT_ROOT}/lib/Lore/src/IDrawable.cpp
    ${PROJECT_ROOT}/lib/Lore/src/Color.cpp
    ${PROJECT_ROOT}/lib/Lore/src/MathHelper.cpp
    ${PROJECT_ROOT}/lib/Lore/src/GameManager.cpp
    ${PROJECT_ROOT}/lib/Lore/src/ITransformable.cpp
    ${PROJECT_ROOT}/lib/Lore/src/private/src/Log.cpp
    ${PROJECT_ROOT}/lib/Lore/src/GameObject.cpp
    ${PROJECT_ROOT}/lib/Lore/src/SoundManager.cpp
    ${PROJECT_ROOT}/lib/Lore/src/Texture.cpp
    ${PROJECT_ROOT}/lib/Lore/src/AssetsManager.cpp
    ${PROJECT_ROOT}/lib/Lore/src/Vector2.cpp
    ${PROJECT_ROOT}/lib/Lore/src/ErrorControl.cpp
    ${PROJECT_ROOT}/src/CreditsScene.cpp
    ${PROJECT_ROOT}/src/MenuScene.cpp
    ${PROJECT_ROOT}/src/SplashScene.cpp
    ${PROJECT_ROOT}/src/Bomber.cpp
    ${PROJECT_ROOT}/src/GameBackground.cpp
    ${PROJECT_ROOT}/src/BombManager.cpp
    ${PROJECT_ROOT}/src/Bomb.cpp
    ${PROJECT_ROOT}/src/Paddle.cpp
    ${PROJECT_ROOT}/src/GameScene.cpp
    ${PROJECT_ROOT}/src/main.cpp
)

##----------------------------------------------------------------------------##
## Executable Definitions                                                     ##
##----------------------------------------------------------------------------##
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR}        )
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS} )
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_MIXER_INCLUDE_DIRS} )
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_TTF_INCLUDE_DIRS}   )

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_LIBRARY}        )
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_MIXER_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_TTF_LIBRARIES}  )
