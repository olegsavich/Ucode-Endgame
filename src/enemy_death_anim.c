#include "../inc/header.h"

void enemy_death_anim(SDL_Renderer *renderer, t_enemy *enemy, int x, int y, double scale) {
    enemy->death_timer += 1;
    if (enemy->death_timer > 1000) {
        enemy->death_timer = 0;
        enemy->damaged = false;
        enemy->isAlive = false;
    }

    SDL_Rect srcrect = {enemy->death_timer / 100 * x, 0, x, y};
    SDL_Rect dstrect = {enemy->rect.x, enemy->rect.y, x * scale, y * scale};

    SDL_RenderCopy(renderer, death_texture, &srcrect, &dstrect);
}
