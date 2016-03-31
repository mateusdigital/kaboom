#!/usr/bin/python

## Imports ##
import os;
import os.path;


## Globals ##
class Globals:
    header_file = open("../include/game_textures.h", "w");
    source_file = open("../src/game_textures.c", "w");

def write_to_header(msg):
    Globals.header_file.write(msg + "\n");

def write_to_source(msg):
    Globals.source_file.write(msg + "\n");

def generate():
    list_images      = os.listdir("../assets");
    list_images_size = len(list_images);

    #Warning Message.
    warning_msg = """/*
                  This file is generate by script
     DO NOT MODIFY IT BY HAND - ALL MODIFICATIONS WILL BE LOST
    AmazingCow - 2016 - Game_Kaboom - genreate_sprite_headers.py
*/"""

    write_to_header(warning_msg);
    write_to_source(warning_msg);

    # Write the begin of include guard on Header file.
    write_to_header("#ifndef __game_textures_h__");
    write_to_header("#define __game_textures_h__");
    write_to_header("\n"); #Some newlines...

    #Write the Textures Size constants
    #and the Textures Array on Header file
    write_to_header("#define GAME_TEXTURES_IDS_SIZE {}".format(list_images_size));
    write_to_header("extern const char* game_textures_ids[GAME_TEXTURES_IDS_SIZE];");

    #Write the header include on Source File.
    write_to_source("#include \"game_textures.h\"\n\n");


    #Iterate over the images and write them...
    for i in xrange(0, list_images_size):
        #Get the filename of image and the 'name'
        #of the image without the extension.
        image_filename = list_images[i];
        name, ext      = os.path.splitext(image_filename);

        #Write the info.
        write_to_header("extern const int game_texture_id_{};".format(name));
        write_to_source("const int game_texture_id_{} = {};".format(name, i));

    #Write the end of include guard on Header file.
    write_to_header("\n"); #Some newlines...
    write_to_header("#endif  /* defined(__game_textures_h__) */");

    #Write the start of the game_textures_ids array on Source file.
    write_to_source("const char* game_textures_ids[GAME_TEXTURES_IDS_SIZE] = {\n");
    #Write the path for the images...
    for i in xrange(0, list_images_size):
        image_filename = list_images[i];
        name, ext      = os.path.splitext(image_filename);

        full_filename   = os.path.join("assets", image_filename);
        texture_id_name = "game_texture_id_{};".format(name);

        write_to_source("   \"{}\", /* {} - {} */\n".format(full_filename,
                                                            i,
                                                            texture_id_name));

    #Write the end of game_texturs_ids array on Source file.
    write_to_source("};");

def main():
    generate();


## Script Initialization ##
if __name__ == '__main__':
    main();
