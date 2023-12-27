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

//This function draws the frame for the time and score tracker
int drawScoreTracker(Image &tracker, ALLEGRO_DISPLAY *display){

    tracker.bitmap = al_load_bitmap("tracker.bmp");
    tracker.x = SCREEN_WIDTH - al_get_bitmap_width(tracker.bitmap);
    tracker.y = 0;

    if(!tracker.bitmap){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }

    al_draw_bitmap(tracker.bitmap, tracker.x, tracker.y, 0);


    return 0;


}

//This function prints the data tracked in the game
void displayTimeAndScore(ALLEGRO_FONT *font, Data &game){

    char printString[200] = "";

    sprintf(printString, "%s's Maze", game.name);
    al_draw_text(font, BLACK, game.tracker.x + 10, 0, ALLEGRO_ALIGN_LEFT, printString);
    sprintf(printString, "TIME: %d", game.time);
    al_draw_text(font, BLACK, game.tracker.x + 10, 50, ALLEGRO_ALIGN_LEFT, printString);
    sprintf(printString, "SCORE: %d", game.score);
    al_draw_text(font, BLACK, game.tracker.x + 10, 75, ALLEGRO_ALIGN_LEFT, printString);
    sprintf(printString, "BEST TIME: %d", game.bestTime);
    al_draw_text(font, BLACK, game.tracker.x + 10, 100, ALLEGRO_ALIGN_LEFT, printString);
    sprintf(printString, "HIGH SCORE: %d", game.highScore);
    al_draw_text(font, BLACK, game.tracker.x + 10, 125, ALLEGRO_ALIGN_LEFT, printString);
    sprintf(printString, "LIVES: %d", game.numberOfLives);
    al_draw_text(font, BLACK, game.tracker.x + 10, 150, ALLEGRO_ALIGN_LEFT, printString);

}

