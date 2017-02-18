##----------------------------------------------------------------------------##
##               █      █                                                     ##
##               ████████                                                     ##
##             ██        ██                                                   ##
##            ███  █  █  ███        Makefile                                  ##
##            █ █        █ █        Game_Kaboom                               ##
##             ████████████                                                   ##
##           █              █       Copyright (c) 2016, 2017                  ##
##          █     █    █     █      AmazingCow - www.AmazingCow.com           ##
##          █     █    █     █                                                ##
##           █              █       N2OMatt - n2omatt@amazingcow.com          ##
##             ████████████         www.amazingcow.com/n2omatt                ##
##                                                                            ##
##                  This software is licensed as GPLv3                        ##
##                 CHECK THE COPYING FILE TO MORE DETAILS                     ##
##                                                                            ##
##    Permission is granted to anyone to use this software for any purpose,   ##
##   including commercial applications, and to alter it and redistribute it   ##
##               freely, subject to the following restrictions:               ##
##                                                                            ##
##     0. You **CANNOT** change the type of the license.                      ##
##     1. The origin of this software must not be misrepresented;             ##
##        you must not claim that you wrote the original software.            ##
##     2. If you use this software in a product, an acknowledgment in the     ##
##        product IS HIGHLY APPRECIATED, both in source and binary forms.     ##
##        (See opensource.AmazingCow.com/acknowledgment.html for details).    ##
##        If you will not acknowledge, just send us a email. We'll be         ##
##        *VERY* happy to see our work being used by other people. :)         ##
##        The email is: acknowledgment_opensource@AmazingCow.com              ##
##     3. Altered source versions must be plainly marked as such,             ##
##        and must not be misrepresented as being the original software.      ##
##     4. This notice may not be removed or altered from any source           ##
##        distribution.                                                       ##
##     5. Most important, you must have fun. ;)                               ##
##                                                                            ##
##      Visit opensource.amazingcow.com for more open-source projects.        ##
##                                                                            ##
##                                  Enjoy :)                                  ##
##----------------------------------------------------------------------------##

################################################################################
## Public Vars                                                                ##
################################################################################
HOST=`uname -s`_`uname -m`


################################################################################
## Private Vars                                                               ##
################################################################################
## Definitions ##
_GAME_NAME=kaboom
_COW_SHARE           = /usr/local/share/amazingcow_game_kaboom
_COW_BIN             = /usr/local/bin
_INSTALL_DIR_DESKTOP = /usr/share/applications
_DESKTOP_FILENAME    = "$(_GAME_NAME).desktop"
_GIT_TAG             = `git tag | sort | tail -1`

## Includes ##
_LORE_INCLUDE_DIR       =  ./lib/Lore
_CORECLOCK_INCLUDE_DIR  =  ./lib/Lore/lib/CoreClock/include
_COREGAME_INCLUDE_DIR   =  ./lib/Lore/lib/CoreGame/include
_CORERANDOM_INCLUDE_DIR =  ./lib/Lore/lib/CoreRandom/include
_GAME_INCLUDE_DIR       =  ./include

## Flags ##
_SDLFLAGS=`sdl2-config --libs --cflags` \
          -lSDL2_image                  \
          -lSDL2_ttf                    \
          -lSDL2_mixer

## CC ##
CC = g++-5 -std=c++14                  \
         -I $(_LORE_INCLUDE_DIR)       \
         -I $(_CORECLOCK_INCLUDE_DIR)  \
         -I $(_COREGAME_INCLUDE_DIR)   \
         -I $(_CORERANDOM_INCLUDE_DIR) \
         -I $(_GAME_INCLUDE_DIR)



################################################################################
## Compilation                                                                ##
################################################################################
# File names
EXEC    = ./build/$(_GAME_NAME)
SOURCES = $(shell find . -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	mkdir -p ./build
	$(CC) $(OBJECTS) -o $(EXEC) $(_SDLFLAGS) -ldl -lstdc++fs

# To obtain object files
%.o: %.cpp
	$(CC) -c $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)


release: CC += -Ofast -Wall -Wextra -Wno-comment \
               -DCOREGAME_RELEASE                \
               -DLORE_RELEASE
release: $(EXEC)

debug: CC += -DDEBUG -g
debug: $(EXEC)


################################################################################
## End user                                                                   ##
################################################################################
install:
	@ echo "---> Installing...".

	@ ## Deleting old stuff...
	 rm -rf $(_COW_SHARE)
	 rm -rf $(_COW_BIN)/$(_GAME_NAME)

	@ ## Install new stuff...
	mkdir -p $(_COW_SHARE)/assets/

	cp -rf ./build/$(_GAME_NAME) $(_COW_BIN)/$(_GAME_NAME) ## Binary
	cp -rf ./assets              $(_COW_SHARE)             ## Assets
	cp -f $(_DESKTOP_FILENAME)   $(_INSTALL_DIR_DESKTOP)   ## .desktop

	@ echo "---> Done... We **really** hope that you have fun :D"


################################################################################
## Release                                                                    ##
################################################################################
gen-binary: $(EXEC)
	mkdir -p ./bin/$(_GAME_NAME)

	cp -r ./assets/              ./bin/$(_GAME_NAME)/assets
	cp    ./build/$(_GAME_NAME)  ./bin/$(_GAME_NAME)/$(_GAME_NAME)
	cp AUTHORS.txt   \
	   CHANGELOG.txt \
	   COPYING.txt   \
	   README.md     \
	   TODO.txt      \
	./bin/$(_GAME_NAME)

	cd ./bin && zip -r ./$(HOST)_$(_GIT_TAG).zip ./$(_GAME_NAME)
	rm -rf ./bin/$(_GAME_NAME)


gen-archive:
	rm -rf   ./archives
	mkdir -p ./archives

	git-archive-all ./archives/source_$(_GAME_NAME)_$(_GIT_TAG).zip
	git-archive-all ./archives/source_$(_GAME_NAME)_$(_GIT_TAG).tar.gz


gen-archive-bin:
	#Clean up the destination folder.
	rm -rf   ./archives-bin
	mkdir -p ./archives-bin

	#Clean up the temp folder.
	rm -rf   $(_GAME_NAME)_game;
	mkdir -p $(_GAME_NAME)_game;

	cp    ./build/$(_GAME_NAME) $(_GAME_NAME)_game;
	cp -R ./assets              $(_GAME_NAME)_game;
	cp    $(_DESKTOP_FILENAME)  $(_GAME_NAME)_game;
	cp    Read_Me.txt           $(_GAME_NAME)_game;

	zip -r    ./archives-bin/$(_GAME_NAME)_$(_GIT_TAG).zip    $(_GAME_NAME)_game
	tar -czvf ./archives-bin/$(_GAME_NAME)_$(_GIT_TAG).tar.gz $(_GAME_NAME)_game


	#Clean up the temp folder.
	rm -rf $(_GAME_NAME)_game;


