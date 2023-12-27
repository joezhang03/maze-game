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

//This function redraws everything when the character and time moves
void reDraw(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int mazeMap[][50], int &row, int &column,
            Image &character, Data &game){

    al_clear_to_color(GREEN);
    generateMaze(display, mazeMap, row, column);
    drawScoreTracker(game.tracker, display);
    displayTimeAndScore(font, game);
    drawCharacter(character);
    al_flip_display();

}
