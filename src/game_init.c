#include "../inc/header.h"

void game_init(void) {
    //initializing plane global variables
    score = 0;
    move_dist = 20;
    count = 0;
    bulletCounter = 0;
    level = 1;
    plane_fire_delay = 2;
    isAlive = true;
    gameState = false;
    lives = 3;
    plane_death_timer = 0;
    skinIndex = 0;
    planeSkin[0] = "resource/img/plane.bmp";
    planeSkin[1] = "resource/img/plane2.bmp";
    planeSkin[2] = "resource/img/plane3.bmp";
    enemies_init();
    init_actor(actor); //initialize actor
    plane_destination = actor->x;
    plane_speed = 1;
    planes = create_lives(); //initialize all plane
    for (int i = 0; i < 10; i++)
        boolets_exist[i] = false;

    //initializing enemy bullets
    for (int i = 0; i < 20; i++)
        enemy_boolets_exist[i] = false;
}
