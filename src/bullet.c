#include "../inc/header.h"

int move_bulllet(int y, int direction) {
    y -= direction;
    return y;
}

int bullet_logic (SDL_Renderer *renderer, int x, int y, int direction) {
    y = move_bulllet(y, direction);
    bullet_draw(renderer, x + 3, y, 59, 122, 0.2);
    return y;
}

bool destroy(int y, bool prev) {
    if(y <= -10)
        return false;
    return prev;
}
