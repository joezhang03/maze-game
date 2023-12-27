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

//This function reads in the maze map from a text file
int readMaze(int mazeMap[][50], int &row, int &column, int &entranceRow, int &entranceColumn, int &exitRow,
             int &exitColumn){

    FILE *fptr;

    //open file
    fptr = fopen("mazeMap.txt", "r");

    //check file setup
    if (!fptr)
        return 1;

    //read in maze size
    fscanf(fptr, "%d", &row);
    fscanf(fptr, "%d", &column);

    //read in entrance coordinates
    fscanf(fptr, "%d", &entranceRow);
    fscanf(fptr, "%d", &entranceColumn);

    //read in exit coordinates
    fscanf(fptr, "%d", &exitRow);
    fscanf(fptr, "%d", &exitColumn);

    //read in maze
    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            fscanf(fptr, "%d", &mazeMap[i][j]);
        }
    }

    //close file
    fclose(fptr);

    return 0;
}

//This function reads the best time and high score from the previous game
int readHighScore(Data &game){

    FILE *file;

    //open file
    file = fopen("highScore.txt", "r");

    if (!file)
        return 1;

    //read in best score and best time
    fscanf(file, "%d", &game.bestTime);
    fscanf(file, "%d", &game.highScore);

    //close file
    fclose(file);

    return 0;

}

//This function saves the best time and high score to a text file
int saveHighScore(Data &game){

    FILE *output;

    //open file
    output = fopen("highScore.txt", "w");

    if (!output)
        return 1;

    //write high score and best time to text file
    if (game.time < game.bestTime || game.bestTime == 0){
        game.bestTime = game.time;
    }

    if (game.score > game.highScore){
        game.highScore = game.score;
    }

    fprintf(output, "%d ", game.bestTime);
    fprintf(output, "%d ", game.highScore);

    //close file
    fclose(output);

    return 0;


}
