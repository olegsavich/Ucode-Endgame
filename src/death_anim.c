#include "../inc/header.h"

void death_anim(SDL_Renderer *renderer, int xpos, int ypos, int x, int y, double scale) {
    plane_death_timer++;

    SDL_Rect srcrect = {plane_death_timer / 25 * x, 0, x, y};
    SDL_Rect dstrect = {xpos, ypos, x * scale, y * scale};

    SDL_RenderCopy(renderer, death_texture, &srcrect, &dstrect);
}
