#include "../inc/header.h"

void enemyArr_draw(SDL_Renderer *renderer, SDL_Texture *texture, t_enemy *arr, double scale) {
    SDL_Rect srcRect = {0, 0, 256, 256};
    SDL_Rect dstRect;
    for (int i = 0; i < 12; i++) {
        if (!arr[i].damaged && arr[i].isAlive) {
            dstRect.x = arr[i].rect.x;
            dstRect.y = arr[i].rect.y;
            dstRect.w = 256 * scale;
            dstRect.h = 256 * scale;
            SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, 0, NULL, 0);
        }
        else {
            if (arr[i].damaged){
                enemy_death_anim(renderer, &arr[i], 191, 195, ENEMY_SIZE);
            }
        }
    }
}
