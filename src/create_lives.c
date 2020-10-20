#include "../inc/header.h"

SDL_Rect *create_lives() {
    SDL_Rect *planes = (SDL_Rect *)malloc(sizeof(SDL_Rect) * lives);
    planes[0].x = 30;
    planes[0].y = 930;
    for (int i = 1; i < lives; i++) {
            planes[i].x = planes[i - 1].x + 70;
            planes[i].y = planes[i - 1].y;
    }
    return planes;
}
