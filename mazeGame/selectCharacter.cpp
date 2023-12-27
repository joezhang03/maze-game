#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

//This function allows the user to select a character skin
int selectCharacter(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, char name[20]){

    //load a bitmap that allows the user to pick the character
    //load another bitmap that indicates the character selected
    Image selectACharacter;
    Image selector;

    selectACharacter.bitmap = al_load_bitmap("selectCharacter.bmp");
    selector.bitmap = al_load_bitmap("characterSelector.bmp");

    if (!selectACharacter.bitmap || !selector.bitmap){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    selectACharacter.x = 0;
    selectACharacter.y = 0;

    al_clear_to_color(GREEN);
    al_draw_bitmap(selectACharacter.bitmap, selectACharacter.x, selectACharacter.y, 0);

    selector.x = SELECTOR_POSITION_X;
    selector.y = SELECTOR_POSITION_Y;

    al_convert_mask_to_alpha(selector.bitmap, WHITE);
    al_draw_bitmap(selector.bitmap, selector.x, selector.y, 0);


    al_flip_display();

    bool doexit = false;

    while (!doexit){

        ALLEGRO_EVENT ev;

        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return 1;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){

            case ALLEGRO_KEY_RIGHT:
                selector.x += SELECTOR_STEP;
                if (selector.x > SELECTOR_POSITION_X + SELECTOR_STEP * 2){
                    selector.x = SELECTOR_POSITION_X;
                }
                break;
            case ALLEGRO_KEY_LEFT:
                selector.x -= SELECTOR_STEP;
                if (selector.x < SELECTOR_POSITION_X){
                    selector.x = SELECTOR_POSITION_X + SELECTOR_STEP * 2;
                }
                break;
            case ALLEGRO_KEY_SPACE:
                if (selector.x == SELECTOR_POSITION_X){
                    strcpy(name, "Ben");
                }
                else if (selector.x == SELECTOR_POSITION_X + SELECTOR_STEP){
                    strcpy(name, "Kyle");
                }
                else if (selector.x == SELECTOR_POSITION_X + SELECTOR_STEP * 2){
                    strcpy(name, "Maria");
                }
                doexit = true;
                break;

            }
        }
        //redraw bitmaps
        al_clear_to_color(GREEN);
        al_draw_bitmap(selectACharacter.bitmap, selectACharacter.x, selectACharacter.y, 0);
        al_convert_mask_to_alpha(selector.bitmap, WHITE);
        al_draw_bitmap(selector.bitmap, selector.x, selector.y, 0);
        al_flip_display();

    }

    return 0;
}
