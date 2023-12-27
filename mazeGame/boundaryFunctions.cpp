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

//This function checks for effects when the user touches objects, monsters or walls
int checkCollision(ALLEGRO_SAMPLE *object, ALLEGRO_SAMPLE *death, Image &character, Data &game, int mazeMap[][50],
                   int &row, int &column, int &entranceRow, int &entranceColumn, int movement){

    //declare variables
    int x = character.x;
    int y = character.y;
    float intv1 = SCREEN_WIDTH*1.0/column;
    float intv2 = SCREEN_HEIGHT*1.0/row;

    //check direction of movement
    switch (movement){

    case 1:
        y = character.y - STEP;
        break;
    case 2:
        y = character.y + STEP;
        break;
    case 3:
        x = character.x - STEP;
        break;
    case 4:
        x = character.x + STEP;
        break;
    }

    //make sure user do not move through walls
    if (mazeMap[(int)(y/intv2)][(int)(x/intv1)] == 0
        || mazeMap[(int)(y /intv2)][(int)((x + al_get_bitmap_width(character.bitmap))/intv1)] == 0
        || mazeMap[(int)((y + al_get_bitmap_height(character.bitmap))/intv2)][(int)(x /intv1)] == 0
        || mazeMap[(int)((y + al_get_bitmap_height(character.bitmap))/intv2)][(int)((x +
        al_get_bitmap_width(character.bitmap))/intv1)] == 0 || x < 0 || y < 0){

        return 1;
    }
    //make user pick up apple cores and increase the score by 10 each time
    else if (mazeMap[(int)((y + al_get_bitmap_height(character.bitmap)*0.5)/intv2)][(int)
             ((x + al_get_bitmap_width(character.bitmap)*0.5)/intv1)] == 2){

        al_play_sample(object, 3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        mazeMap[(int)((y + al_get_bitmap_height(character.bitmap)*0.5)/intv2)]
                [(int)((x + al_get_bitmap_width(character.bitmap)*0.5)/intv1)] = 1;
        game.score += 10;
    }
    //make user pick up plastic bottles and increase the score by 100 each time
    else if (mazeMap[(int)((y + al_get_bitmap_height(character.bitmap)*0.5)/intv2)][(int)
             ((x + al_get_bitmap_width(character.bitmap)*0.5)/intv1)] == 3){

        al_play_sample(object, 3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        mazeMap[(int)((y + al_get_bitmap_height(character.bitmap)*0.5)/intv2)]
                [(int)((x + al_get_bitmap_width(character.bitmap)*0.5)/intv1)] = 1;
        game.score += 100;
    }
    //make the player die when they touch a ghost
    else if (mazeMap[(int)((y + al_get_bitmap_height(character.bitmap)*0.5)/intv2)][
             (int)((x + al_get_bitmap_width(character.bitmap)*0.5)/intv1)] == 4){

        //make the player lose a life each time they die
        game.numberOfLives --;
        //the game ends after the player loses all their lives
        if (game.numberOfLives <= 0){
            return 2;
        }
        //if the player still have lives, they will go back to the entrance, but the score will be the same
        else if (game.numberOfLives > 0){
            resetCharacter(death, character, row, column, entranceRow, entranceColumn);
        }
    }
    //make the number of lives increase by one when the player touches an extra life
    else if (mazeMap[(int)((y + al_get_bitmap_height(character.bitmap)*0.5)/intv2)][(int)
             ((x + al_get_bitmap_width(character.bitmap)*0.5)/intv1)] == 5){

        //make the user gain one life
        game.numberOfLives++;
        al_play_sample(object, 3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        mazeMap[(int)((y + al_get_bitmap_height(character.bitmap)*0.5)/intv2)]
                [(int)((x + al_get_bitmap_width(character.bitmap)*0.5)/intv1)] = 1;
    }

    return 0;

}

