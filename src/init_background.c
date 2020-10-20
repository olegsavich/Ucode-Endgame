#include "../inc/header.h"

SDL_Texture *init_background(SDL_Renderer *renderer, char const *path) {
    SDL_Surface *back_surface = NULL;
    SDL_Texture *background = NULL;
    back_surface = SDL_LoadBMP(path);
    if (!back_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        return NULL;
    }
    background = SDL_CreateTextureFromSurface(renderer, back_surface);
    if (!background) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return NULL;
    }
    SDL_FreeSurface(back_surface);
    return background;
}
