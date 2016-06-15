
#!/bin/bash
LORE_DIR=./lib/Lore
CORECLOCK_DIR=$LORE_DIR/lib/CoreClock
COREGAME_DIR=$LORE_DIR/lib/CoreGame
CORERANDOM_DIR=$LORE_DIR/lib/CoreRandom

# -DKABOOM_DEBUG
SDLFLAGS="$(sdl2-config --static-libs --cflags) -lSDL2_image -lSDL2_ttf -lSDL2_mixer"
CC="g++ -Ofast -std=c++11 -Wall -Wextra -Wno-comment  -DCOREGAME_RELEASE -DLORE_RELEASE"

$CC -o game_static.exe               \
    -I $LORE_DIR                     \
    -I $CORECLOCK_DIR/include        \
    -I $COREGAME_DIR/include         \
    -I $CORERANDOM_DIR/include       \
    -I ./include                     \
                                     \
    $LORE_DIR/src/*.cpp              \
    $LORE_DIR/src/private/src/*.cpp  \
    $CORECLOCK_DIR/src/*.cpp         \
    $COREGAME_DIR/src/*.cpp          \
    $CORERANDOM_DIR/src/*.cpp        \
    ./src/*.cpp                      \
                                     \
$SDLFLAGS

