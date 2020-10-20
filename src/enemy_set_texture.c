#include "../inc/header.h"

void enemy_set_texture(SDL_Renderer *renderer, char* path, SDL_Texture **arr) {
    SDL_Surface* surface = load_surface(path);
    for (int i = 0; i < 12; i++)
        arr[i] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}
