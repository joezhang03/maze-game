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

int loadInstructions(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *event_queue){

    char printString[200] = "";

    al_clear_to_color(GREEN);

    sprintf(printString, "Instructions");
    al_draw_text(font, BLACK, SCREEN_WIDTH/2, 0, ALLEGRO_ALIGN_CENTER, printString);

    sprintf(printString, "Use arrow keys to move");
    al_draw_text(font, BLACK, 0, 50, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "Press escape at any time to exit once game has started");
    al_draw_text(font, BLACK, 0, 100, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "Move to the exit on the other side of the maze to win");
    al_draw_text(font, BLACK, 0, 150, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "Pick up apple cores and plastic bottles throughout the maze");
    al_draw_text(font, BLACK, 0, 200, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "An apple core increases the score by 10 and a plastic bottle increases the score by 100");
    al_draw_text(font, BLACK, 0, 250, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "Avoid while ghosts, they take away one life from you each time you touch them");
    al_draw_text(font, BLACK, 0, 300, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "You have 3 lives, if you lose all lives, the game ends");
    al_draw_text(font, BLACK, 0, 350, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "Each time a heart is picked up, you get an extra life");
    al_draw_text(font, BLACK, 0, 400, ALLEGRO_ALIGN_LEFT, printString);

    sprintf(printString, "Press space to continue");
    al_draw_text(font, BLACK, 0, 550, ALLEGRO_ALIGN_LEFT, printString);

    al_flip_display();

    bool doexit = false;

    while (!doexit){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            return -1;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
                doexit = true;
            }
        }
    }

    return 0;
}
