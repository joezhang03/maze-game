#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

//This function loads the character bitmap to the screen
int loadCharacter(ALLEGRO_DISPLAY *display, Image &character, char name[20]){

    //character.bitmap = al_load_bitmap("characterbak.bmp");
    if (strcmp(name, "Ben") == 0){
        character.bitmap = al_load_bitmap("character1.bmp");
    }
    else if (strcmp(name, "Kyle") == 0){
        character.bitmap = al_load_bitmap("character2.bmp");
    }
    else if (strcmp(name, "Maria") == 0){
        character.bitmap = al_load_bitmap("character3.bmp");
    }

    if(!character.bitmap){
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }

    return 0;

}

//This function draws the character
void drawCharacter(Image character){

    //make the white background of bitmap transparent
    al_convert_mask_to_alpha(character.bitmap, WHITE);

    //draw character to the screen
    al_draw_bitmap(character.bitmap, character.x, character.y, 0);

}

//This function makes the character move and counts time
int moveCharacter(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue,
                  ALLEGRO_FONT *font, ALLEGRO_TIMER *timer, ALLEGRO_SAMPLE *death,
                  ALLEGRO_SAMPLE *object, Image &character, Data &game, int mazeMap[][50],
                  int &row, int &column, int &entranceRow, int &entranceColumn, int &exitRow,
                  int &exitColumn, ALLEGRO_SAMPLE *sample){

    bool doexit = false;

    //move character around the maze using keyboard
    while (!doexit){

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            doexit = true;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    if (checkCollision(object, death, character, game, mazeMap, row, column, entranceRow,
                                       entranceColumn, 1) == 0)

                        character.y -= STEP;

                    else if (checkCollision(object, death, character, game, mazeMap, row, column, entranceRow,
                                            entranceColumn, 1) == 2)

                        return 2;

                    break;
                case ALLEGRO_KEY_DOWN:
                    if (checkCollision(object, death, character, game, mazeMap, row, column, entranceRow,
                                       entranceColumn, 2) == 0)

                        character.y += STEP;

                    else if (checkCollision(object, death, character, game, mazeMap, row, column, entranceRow,
                                            entranceColumn, 2) == 2)

                        return 2;

                    break;
                case ALLEGRO_KEY_LEFT:
                    if (checkCollision(object, death, character, game, mazeMap, row, column, entranceRow,
                                       entranceColumn, 3) == 0)

                        character.x -= STEP;

                    else if (checkCollision(object, death, character, game, mazeMap, row, column, entranceRow,
                                            entranceColumn, 3) == 2)

                        return 2;

                    break;
                case ALLEGRO_KEY_RIGHT:
                    if (checkCollision(object, death, character, game, mazeMap, row, column, entranceRow,
                                       entranceColumn, 4) == 0)

                        character.x += STEP;

                    else if (checkCollision(object, death, character, game, mazeMap, row, column, entranceRow,
                                            entranceColumn, 4) == 2)

                        return 2;

                    break;
                case ALLEGRO_KEY_ESCAPE:
                    doexit = true;
                    break;
            }
            //redraw maze game each time character moves
            reDraw(display, font, mazeMap, row, column, character, game);
            if (checkWin(display, timer, character, mazeMap, row, column, exitRow, exitColumn, sample) == 1)
                return 1;
        }
        //track time used in the game
        else if (ev.type == ALLEGRO_EVENT_TIMER){
            if (ev.timer.source == timer){
                game.time++;
                reDraw(display, font, mazeMap, row, column, character, game);
                moveMonster(mazeMap, row, column);
            }
        }
    }

    return 0;
}

