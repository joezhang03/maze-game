#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "maze.h"

//This function draws the maze with all the monsters, garbage objects and extra lives
int generateMaze(ALLEGRO_DISPLAY *display, int mazeMap[][50], int &row, int &column){

    Image appleCore;
    Image bottle;
    Image ghost;
    Image extraLife;

    //load bitmaps for apple cores and bottles across the maze
    appleCore.bitmap = al_load_bitmap("appleCore.bmp");
    bottle.bitmap = al_load_bitmap("bottle.bmp");
    ghost.bitmap = al_load_bitmap("ghost.bmp");
    extraLife.bitmap = al_load_bitmap("extraLife.bmp");
    if (!appleCore.bitmap){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr,
                                       ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }

    if (!bottle.bitmap){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }

    if (!ghost.bitmap){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    if (!extraLife.bitmap){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            //draw walls in the maze
            if (mazeMap[i][j] == 0){
                al_draw_filled_rectangle(j*SCREEN_WIDTH/column, i*SCREEN_HEIGHT/row,
                                         (j+1)*SCREEN_WIDTH/column, (i+1)*SCREEN_HEIGHT/row, BLACK);
            }
            else if (mazeMap[i][j] == 2){
                //draw apple cores across the maze
                appleCore.x = j*SCREEN_WIDTH/column;
                appleCore.y = i*SCREEN_HEIGHT/row;
                al_convert_mask_to_alpha(appleCore.bitmap, WHITE);
                al_draw_bitmap(appleCore.bitmap, appleCore.x, appleCore.y, 0);
            }
            else if (mazeMap[i][j] == 3){
                //draw plastic bottles across the maze
                bottle.x = j*SCREEN_WIDTH/column;
                bottle.y = i*SCREEN_HEIGHT/row;
                al_convert_mask_to_alpha(bottle.bitmap, WHITE);
                al_draw_bitmap(bottle.bitmap, bottle.x, bottle.y, 0);
            }
            else if (mazeMap[i][j] == 4){
                //draw monsters across the maze
                ghost.x = j*SCREEN_WIDTH/column;
                ghost.y = i*SCREEN_HEIGHT/row;
                al_convert_mask_to_alpha(ghost.bitmap, PINK);
                al_draw_bitmap(ghost.bitmap, ghost.x, ghost.y, 0);
            }
            else if (mazeMap[i][j] == 5){
                //draw extra lives across the maze
                extraLife.x = j*SCREEN_WIDTH/column;
                extraLife.y = i*SCREEN_HEIGHT/row;
                al_convert_mask_to_alpha(extraLife.bitmap, WHITE);
                al_draw_bitmap(extraLife.bitmap, extraLife.x, extraLife.y, 0);
            }
        }
    }

    return 0;
}
