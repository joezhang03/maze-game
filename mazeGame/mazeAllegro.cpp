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

//This function initializes allegro
int initializeAllegro(){

    //initialize allegro
    al_init();

    //install font
    al_init_font_addon();
    al_init_ttf_addon();

    //install audio
    al_install_audio();
    al_init_acodec_addon();

    //reserve samples
    al_reserve_samples(5);

    return 0;
}

//This function checks setup for different allegro pointers
int checkSetup(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_SAMPLE *sample,
               ALLEGRO_FONT *font, ALLEGRO_FONT *credits, ALLEGRO_TIMER *timer, ALLEGRO_SAMPLE *death,
               ALLEGRO_SAMPLE *objectPickup, ALLEGRO_SAMPLE *gameEnd, ALLEGRO_SAMPLE *win){

    //check display setup
    if (!display){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //check primitives addon setup
    if (!al_init_primitives_addon()){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize primitives addon!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //check image addon
    if (!al_init_image_addon()){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //check keyboard setup
    if (!al_install_keyboard()){
        al_show_native_message_box(display, "Error", "Error", "Failed to install keyboard!", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //check event queue setup
    if (!event_queue){
        al_show_native_message_box(display, "Error", "Error", "Failed to create event queue!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -1;
    }

    //check music setup
    if (!sample || !death || !objectPickup || !gameEnd || !win){
        al_show_native_message_box(display, "Error", "Error", "Failed to create sample!", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //check font setup
    if (!font){
        al_show_native_message_box(display, "Error", "Error", "Failed to load Lemon_Juice.ttf", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //check font setup
    if (!credits){
        al_show_native_message_box(display, "Error", "Error", "Failed to load Lemon_Juice.ttf", nullptr,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //check timer setup
    if (!timer){
        al_show_native_message_box(display, "Error", "Error", "Failed to load timer", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    return 0;
}

//This function registers the different events for the event queue
void registerEventQueue(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer){

    //register event queue for display events, keyboard and timer
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

}

