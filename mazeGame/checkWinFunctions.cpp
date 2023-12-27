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

//This function checks if player has won the game
int checkWin(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, Image character, int mazeMap[][50], int row,
             int column, int exitRow, int exitColumn, ALLEGRO_SAMPLE *sample){

    if ((character.x > (exitColumn - 1) * SCREEN_WIDTH/column && character.x > exitColumn *SCREEN_WIDTH/column)
        && (character.y > (exitRow - 1) * SCREEN_HEIGHT/row && character.y > exitRow + 5 * SCREEN_HEIGHT/row)){

        //free up memory
        al_destroy_timer(timer);
        al_destroy_bitmap(character.bitmap);
        al_destroy_sample(sample);

        return 1;
    }

    return 0;
}

//This function tells the user that they have won and asks if user wants to replay or exit
int winInput(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue){

    Image youWin;

    youWin.x = 0;
    youWin.y = 0;

    bool doexit = false;

    youWin.bitmap = al_load_bitmap("youWin.bmp");

    if (!youWin.bitmap){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr,
                                       ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }

    al_convert_mask_to_alpha(youWin.bitmap, PINK);

    al_draw_bitmap(youWin.bitmap, youWin.x, youWin.y, 0);

    al_flip_display();

    while (!doexit){

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return -1;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){

            case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;
            case ALLEGRO_KEY_1:
                return 1;
                break;
            }
        }
    }

    return 0;
}

//This function tells the user that they have lost and if they want to replay or exit
int loseInput(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue){

    Image gameOver;

    gameOver.x = 0;
    gameOver.y = 0;

    bool doexit = false;

    gameOver.bitmap = al_load_bitmap("gameOver.bmp");

    if (!gameOver.bitmap){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_clear_to_color(BLACK);

    al_draw_bitmap(gameOver.bitmap, gameOver.x, gameOver.y, 0);

    al_flip_display();

      while (!doexit){

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return -1;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){

            case ALLEGRO_KEY_ESCAPE:
                doexit = true;
                break;
            case ALLEGRO_KEY_1:
                return 1;
            }
        }
    }

    return 0;


}
