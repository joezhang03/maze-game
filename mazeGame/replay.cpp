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

//This function lets the user replay the game
int replay(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font, ALLEGRO_TIMER *timer,
           ALLEGRO_SAMPLE *sample, ALLEGRO_SAMPLE *death, ALLEGRO_SAMPLE *gameEnd, ALLEGRO_SAMPLE *object,
           ALLEGRO_SAMPLE *win, Image &character, Data &game, int mazeMap[][50], int &row, int &column,
           int &entranceRow, int &entranceColumn, int &exitRow, int &exitColumn, int &a, int &b, int &c){

    while (a == 1 || b == 1){

        //reinitialize event queue and music
        event_queue = al_create_event_queue();
        sample = al_load_sample("mazeMusic.ogg");

        //register event queue
        registerEventQueue(event_queue, display, timer);

        //read maze from a text file
        readMaze(mazeMap, row, column, entranceRow, entranceColumn, exitRow, exitColumn);
        //clear screen
        al_clear_to_color(GREEN);
        //draw maze to screen
        generateMaze(display, mazeMap, row, column);
        al_flip_display();

        //read best time and high score
        readHighScore(game);

        //draw time and score tracker to the screen and display time and score
        game.time = 0;
        game.score = 0;
        game.numberOfLives = 3;
        drawScoreTracker(game.tracker, display);
        displayTimeAndScore(font, game);
        al_flip_display();

        //draw character to the screen
        character.x = entranceColumn * SCREEN_WIDTH/column;
        character.y = entranceRow * SCREEN_HEIGHT/row;
        loadCharacter(display, character, game.name);
        drawCharacter(character);
        al_flip_display();

        //play music
        al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);

        //start timer
        al_start_timer(timer);

        //move character around the screen
        c = moveCharacter(display, event_queue, font, timer, death, object, character, game, mazeMap,
                          row, column, entranceRow, entranceColumn, exitRow, exitColumn, sample);
        if (c == 1){
            //write high score to file
            saveHighScore(game);
            //play win music
            al_play_sample(win, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
            //ask user for input after they have won
            a = winInput(display, event_queue);
            //initialize the lose variable to 0 if the win variable is 0
            if (a == 0){
                b = 0;
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
            b = loseInput (display, event_queue);
            //initialize the win variable to 0 if the lose variable is 0
            if (b == 0){
                a = 0;
            }
        }
        else if (c == 0){
            break;
        }
    }

    //free up memory
    al_destroy_sample(sample);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;

}
