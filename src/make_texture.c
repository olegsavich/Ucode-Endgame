#include "../inc/header.h"

void make_texture(SDL_Renderer *renderer, char* path, int xpos, int ypos, int x, int y, double scale) {
    SDL_Surface* surface = load_surface(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect srcRect = {0, 0, x, y};
    SDL_Rect dstRect = {xpos, ypos, x * scale, y * scale};

    SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0, NULL, 0);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
