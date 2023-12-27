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

//This function loads the credits screen
int loadCredits(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *event_queue, Image title){

    char printString[200] = "";

    al_clear_to_color(GREEN);

    //print credits
    sprintf(printString, "Credits");
    al_draw_text(font, BLACK, SCREEN_WIDTH/2, 10, ALLEGRO_ALIGN_CENTER, printString);

    sprintf(printString, "Developed by: Joe Zhang");
    al_draw_text(font, BLACK, 0, 100, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "Graphics by: Joe Zhang");
    al_draw_text(font, BLACK, 0, 200, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "Music by: MDK");
    al_draw_text(font, BLACK, 0, 300, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "Sound effects from: Super Mario Bros");
    al_draw_text(font, BLACK, 0, 400, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "Press B to go back");
    al_draw_text(font, BLACK, 0, SCREEN_HEIGHT - 100, ALLEGRO_ALIGN_LEFT, printString);

    al_flip_display();

    bool doexit = false;

    //allow user to go back to title screen
    while (!doexit){

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return -1;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){

            case ALLEGRO_KEY_B:
                drawTitlePage(title);
                al_flip_display();
                doexit = true;
                break;
            }
        }
    }

    return 0;

}
