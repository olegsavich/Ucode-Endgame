#include "../inc/header.h"

int eBullet_logic (SDL_Renderer *renderer, int x, int y, int direction) {
    y = move_bulllet(y, direction);
    eBullet_draw(renderer, x + 3, y, 59, 122, 0.2);
    return y;
}

bool eBullet_destroy(int y, bool prev) {
    if(y >= 1000) {
        return false;
    }
    return prev;
}
