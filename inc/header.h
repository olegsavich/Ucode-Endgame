#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <unistd.h>
#define LIVES_SIZE 0.2
#define ACTOR_SIZE 0.4
#define ENEMY_SIZE 0.2
#define BUTTON_SIZE 0.6

int score;
bool comeBack;
SDL_Texture *death_texture;
SDL_Texture *init_background(SDL_Renderer *renderer, char const *path);
SDL_Surface *load_surface(char const *path);
void make_texture(SDL_Renderer *renderer, char* path, int xpos, int ypos, int x, int y, double scale);
void game_init(void);
int level;
void enemies_init(void);
char *mx_intToChar(int n);
SDL_Texture *gameOver;
//music
Mix_Music *menuMusic;
Mix_Chunk *plane_shot;
Mix_Chunk *enemy_shot;
Mix_Chunk *explousion;
bool loadMedia();
//plane
int move_dist;
unsigned int plane_fire_delay;
int plane_destination;
int plane_speed;
int lives;
bool isAlive;
bool gameState;
int plane_death_timer;
char *planeSkin[3];
int skinIndex;
void init_actor(SDL_Rect *actor);
SDL_Rect *create_lives();
SDL_Rect *actor;
SDL_Rect *planes;
void death_anim(SDL_Renderer *renderer, int xpos, int ypos, int x, int y, double scale);

//bullet
int count;
typedef struct s_bullet {
    int x;
    int y;
    bool created;
}              t_bullet;
typedef struct s_enemyBullet {
    int x;
    int y;
    bool created;
}              t_enemyBullet;
int bulletCounter;
t_bullet bul[10];
bool boolets_exist[10];
t_enemyBullet ebul[20];
bool enemy_boolets_exist[20];
SDL_Texture *bullet_texture;
SDL_Texture *eBullet_texture;
int move_bulllet(int y, int direction);
int bullet_logic (SDL_Renderer *renderer,int x, int y, int direction);
int eBullet_logic (SDL_Renderer *renderer, int x, int y, int direction);
bool destroy(int y, bool prev); //in the bullet_logic.c
bool eBullet_destroy(int y, bool prev);
void bullet_draw(SDL_Renderer *renderer, int xpos, int ypos, int x, int y, double scale);
void eBullet_draw(SDL_Renderer *renderer, int xpos, int ypos, int x, int y, double scale);

//enemy
typedef struct s_enemy {
    SDL_Rect rect;
    bool isAlive;
    bool damaged;
    int death_timer;
}              t_enemy;
int enemy_count;
int direction_movement;
char *enemySkin[3];
t_enemy enemyArray[3][12];
void enemyArr_draw(SDL_Renderer *renderer, SDL_Texture *texture, t_enemy *arr, double scale);
void enemy_set_texture(SDL_Renderer *renderer, char* path, SDL_Texture **arr);
void enemy_death_anim(SDL_Renderer *renderer, t_enemy *enemy, int x, int y, double scale);
