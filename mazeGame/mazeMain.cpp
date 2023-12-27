/*******************************************************************
*  Name: Joe Zhang                                                 *
*  Class: ICS 3U-01                                                *
*  Teacher: Ms. Cullum                                             *
*  Date: December 2nd, 2019                                        *
*  Project: Summative maze game                                    *
*  Due date: January 17th, 2020                                    *
*  Music: MDK - Press Start                                        *
*  Known Issues: N/A                                               *
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
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

int main(int argc, char **argv){

    /***************SET UP ALLEGRO****************/
    //initialize allegro
    initializeAllegro();

    //initialize display and check setup
    ALLEGRO_DISPLAY *display = nullptr;
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    event_queue = al_create_event_queue();
    ALLEGRO_SAMPLE *sample = nullptr;
    sample = al_load_sample("mazeMusic.ogg");
    ALLEGRO_SAMPLE *death = nullptr;
    death = al_load_sample("death.ogg");
    ALLEGRO_SAMPLE *gameEnd = nullptr;
    gameEnd = al_load_sample("gameOver.ogg");
    ALLEGRO_SAMPLE *objectPickup = nullptr;
    objectPickup = al_load_sample ("objectSound.ogg");
    ALLEGRO_SAMPLE *win = nullptr;
    win = al_load_sample ("winSound.ogg");
    ALLEGRO_FONT *font = nullptr;
    font = al_load_ttf_font("Lemon_Juice.ttf", 28, 0);
    ALLEGRO_FONT *credits = nullptr;
    credits = al_load_ttf_font("Lemon_Juice.ttf", 48, 0);
    ALLEGRO_TIMER *timer = nullptr;
    timer = al_create_timer(1.0);

    //check allegro setup
    checkSetup(display, event_queue, sample, font, credits, timer, death, objectPickup, gameEnd, win);

    //register events for event queue
    registerEventQueue(event_queue, display, timer);

    //set window title
    al_set_window_title(display, "Environmental Maze Game");

    /******************CREATE TITLE PAGE********************/
    //load and draw title page to the screen
    Image title;
    loadTitlePage(display, title);
    drawTitlePage(title);
    al_flip_display();
    //allow user to press a key to continue to game
    //Game will exit with no errors if escape key is pressed
    if (continueToGame(display, event_queue, credits, title) == -1)
        return 0;

    /*******************SELECT CHARACTER*********************/
    Data gameData;
    //exit with no errors if display is closed
    if (selectCharacter(display, event_queue, gameData.name) == 1)
        return 0;

    /*******************LOAD IMSTRUCTIONS*******************/
    //exit with no errors if display is closed
    if (loadInstructions(font, event_queue) == -1)
        return 0;

    /******************CREATE MAZE MAP**********************/
    //read in map from text file
    int row;
    int column;
    int entranceRow;
    int entranceColumn;
    int exitRow;
    int exitColumn;
    int mazeMap[MAX_ROWS][MAX_COLS];
    readMaze(mazeMap, row, column, entranceRow, entranceColumn, exitRow, exitColumn);
    //generate maze to game screen
    al_clear_to_color(GREEN);
    generateMaze(display, mazeMap, row, column);
    //display maze
    al_flip_display();

    /***************CREATE TIMER AND SCORE TRACKER******************/
    //read in best time and high score
    readHighScore(gameData);

    //draw time and score tracker to screen and track time and score
    gameData.time = 0;
    gameData.score = 0;
    gameData.numberOfLives = 3;
    drawScoreTracker(gameData.tracker, display);
    displayTimeAndScore(font, gameData);
    //display time tracker
    al_flip_display();

    /****************CREATE CHARACTER**********************/
    Image character;

    //load and draw character
    character.x = entranceColumn * SCREEN_WIDTH/column;
    character.y = entranceRow * SCREEN_HEIGHT/row;
    loadCharacter(display, character, gameData.name);
    drawCharacter(character);
    //display character
    al_flip_display();

    /*********************PLAY MUSIC**********************/
    //play game music (MDK - PRESS START)
    al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);

    /********************START TIMER**********************/
    al_start_timer(timer);

    /*******************MOVE CHARACTER********************/
    //variables that determine the return values of the win input and lose input functions
    int a;
    int b;
    int c;

    //move character around the maze with keyboard
    c = moveCharacter(display, event_queue, font, timer, death, objectPickup, character, gameData,
                      mazeMap, row, column, entranceRow, entranceColumn, exitRow, exitColumn, sample);
    if (c == 1){
        //write high score to file
        saveHighScore(gameData);
        //play win music
        al_play_sample(win, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        //ask user for input after they have won
        a = winInput(display, event_queue);
        if (a == 1){
            replay(display, event_queue, font, timer, sample, death, gameEnd, objectPickup,
                   win, character, gameData, mazeMap, row, column, entranceRow, entranceColumn,
                   exitRow, exitColumn, a, b, c);
        }
    }
    else if (c == 2){
        al_destroy_sample(sample);
        //play death music
        al_play_sample(death, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        //wait 3 seconds
        al_rest(3.0);
        //play game over music
        al_play_sample(gameEnd, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
        //ask user for input after they have lost
        b = loseInput(display, event_queue);
        if (b == 1){
            replay(display, event_queue, font, timer, sample, death, gameEnd, objectPickup,
                   win, character, gameData, mazeMap, row, column, entranceRow, entranceColumn,
                   exitRow, exitColumn, a, b, c);
        }
    }
    else if (c == 0){
        //free up memory if user exits game
        al_destroy_sample(sample);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
    }

    //free up memory
    al_destroy_sample(death);
    al_destroy_sample(gameEnd);
    al_destroy_sample(objectPickup);
    al_destroy_sample(win);
    al_destroy_font(font);
    al_destroy_display(display);

    //exit with no errors
    return 0;
}
