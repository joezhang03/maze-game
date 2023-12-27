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

//This function moves the user back to the entrance after they lose a life
int resetCharacter(ALLEGRO_SAMPLE *death, Image &character, int row, int column, int entranceRow, int entranceColumn){

    //play death sound
    al_play_sample(death, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
    //wait 3 seconds
    al_rest(3.0);

    //redraw character to the entrance
    character.x = entranceColumn * SCREEN_WIDTH/column;
    character.y = entranceRow * SCREEN_HEIGHT/row;


    return 0;
}
