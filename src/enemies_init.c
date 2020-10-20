#include "../inc/header.h"

void enemies_init(void) {
    //initializing enemy global variables
    direction_movement = 35;
    enemy_count = 36;
    enemySkin[0] = "resource/img/enemy1.bmp";
    enemySkin[1] = "resource/img/enemy2.bmp";
    enemySkin[2] = "resource/img/enemy3.bmp";
    enemyArray[0][0].rect.x = 450;
    enemyArray[0][0].rect.y = 100;
    enemyArray[0][0].isAlive = true;
    enemyArray[0][0].damaged = false;
    enemyArray[0][0].death_timer = 0;
    enemyArray[1][0].rect.x = 450;
    enemyArray[1][0].rect.y = 170;
    enemyArray[1][0].isAlive = true;
    enemyArray[1][0].damaged = false;
    enemyArray[1][0].death_timer = 0;
    enemyArray[2][0].rect.x = 450;
    enemyArray[2][0].rect.y = 240;
    enemyArray[2][0].isAlive = true;
    enemyArray[2][0].damaged = false;
    enemyArray[2][0].death_timer = 0;
    for (int i = 0; i < 3; i++) {
            for (int j = 1; j < 12; j++) {
                    enemyArray[i][j].rect.x = enemyArray[i][j - 1].rect.x + 60;
                    enemyArray[i][j].rect.y = enemyArray[i][j - 1].rect.y;
                    enemyArray[i][j].isAlive = true;
                    enemyArray[i][j].death_timer = 0;
                    enemyArray[i][j].damaged = false;
            }
    }
}
