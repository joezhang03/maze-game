#include <stdio.h>
#include <time.h>
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

//This function moves the monsters automatically
int moveMonster(int mazeMap[][50], int &row, int &column){

    int movement;

    //seed the random number generator
    srand(time(0));

    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            if (mazeMap[i][j] == 4){
                //assign a random number for the monster's movement
                movement = rand() % 4 + 1;
                switch (movement){

                case 1:
                    if (i > 0 && mazeMap[i-1][j] == 1){
                        mazeMap[i][j] = 1;
                        mazeMap[i-1][j] = 10;
                    }
                    break;
                case 2:
                    if (i < row && mazeMap[i+1][j] == 1){
                        mazeMap[i][j] = 1;
                        mazeMap[i+1][j] = 10;
                    }
                    break;
                case 3:
                    if (j > 0 && mazeMap[i][j-1] == 1){
                        mazeMap[i][j] = 1;
                        mazeMap[i][j-1] = 10;
                    }
                    break;
                case 4:
                    if (j < column && mazeMap[i][j+1] == 1){
                        mazeMap[i][j] = 1;
                        mazeMap[i][j+1] = 10;
                    }
                    break;
                }
            }
        }
    }

    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            if (mazeMap[i][j] == 10){
                mazeMap[i][j] = 4;
            }
        }
    }

    return 0;

}


