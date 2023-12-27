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

//This function loads the title page
int loadTitlePage(ALLEGRO_DISPLAY *display, Image &title){

    title.bitmap = al_load_bitmap("title.bmp");

    if (!title.bitmap){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image", nullptr,
                                  ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    return 0;

}

//This function draws the title page
void drawTitlePage(Image &title){

    title.x = 0;
    title.y = 0;

    al_draw_bitmap(title.bitmap, title.x, title.y, 0);
}

//This function asks for user input to continue to game, load credits or quit
int continueToGame(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font, Image title){

    bool doexit = false;

    while (!doexit){

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return -1;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){

            case ALLEGRO_KEY_C:
                //load credits screen
                //exit with no errors if display is closed
                if (loadCredits(font, event_queue, title) == -1)
                    return -1;
                break;
            case ALLEGRO_KEY_SPACE:
                doexit = true;
                break;
            case ALLEGRO_KEY_ESCAPE:
                return -1;
                break;
            }
        }
    }

    return 0;

}

