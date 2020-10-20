#include "../inc/header.h"

void bullet_draw(SDL_Renderer *renderer, int xpos, int ypos, int x, int y, double scale) {
    SDL_Rect srcRect = {0, 0, x, y};
    SDL_Rect dstRect = {xpos, ypos, x * scale, y * scale};

    SDL_RenderCopyEx(renderer, bullet_texture, &srcRect, &dstRect, 0, NULL, 0);
}
