#include "../inc/header.h"

int main(int argc, char *argv[])
{   
        TTF_Init();
        menuMusic = NULL;
    //The sound effects that will be used
    plane_shot = NULL;
    enemy_shot = NULL;
    explousion = NULL;
    comeBack = false;
    int Mx = 0;
    int My = 0;
    lives = 3;
    planes = create_lives(); //initialize all planes
    actor = &planes[lives - 1];
    //SDL conserned variables
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    game_init();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn’t initialize SDL: %s", SDL_GetError());
        return 3;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return 3;
    }
    //CREATE WINDOW
    if (SDL_CreateWindowAndRenderer(1500, 1000, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

        TTF_Font* Pixel = TTF_OpenFont("resource/fonts/FFFFORWA.TTF", 24); //this opens a font style and sets a size

        SDL_Color White = {255, 255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Pixel, "Score :", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

        SDL_Rect Message_rect; //create a rect
        Message_rect.x = 1100;  //controls the rect's x coordinate 
        Message_rect.y = 925; // controls the rect's y coordinte
        Message_rect.w = 200; // controls the width of the rect
        Message_rect.h = 80; // controls the height of the rect

        SDL_Rect Score_rect; //create a rect
        Score_rect.x = 1300;  //controls the rect's x coordinate 
        Score_rect.y = 925; // controls the rect's y coordinte
        Score_rect.w = 150; // controls the width of the rect
        Score_rect.h = 80; // controls the height of the rect


    SDL_Surface* overSurface = load_surface("resource/img/GAME_OVER.bmp");
    gameOver = SDL_CreateTextureFromSurface(renderer, overSurface);
    SDL_FreeSurface(overSurface);

    SDL_Surface* death_surface = load_surface("resource/img/explosions.bmp");
    death_texture = SDL_CreateTextureFromSurface(renderer, death_surface); //DEATH_TEXTURE
    SDL_FreeSurface(death_surface);

    SDL_Surface* bullet_surface = load_surface("resource/img/albullet.bmp");
    bullet_texture = SDL_CreateTextureFromSurface(renderer, bullet_surface);
    SDL_FreeSurface(bullet_surface);

    SDL_Surface* eBullet_surface = load_surface("resource/img/eBullet.bmp");
    eBullet_texture = SDL_CreateTextureFromSurface(renderer, eBullet_surface);
    SDL_FreeSurface(eBullet_surface);

    SDL_Texture *background = init_background(renderer, "resource/img/background3.bmp");
    SDL_Texture *background_menu = init_background(renderer,"resource/img/background2.bmp" );
    Uint32 ticks = SDL_GetTicks();
    Uint32 curr_seconds = ticks / 1000;
    Uint32 prev_seconds = curr_seconds; //for enemy movement

    //other variables
    SDL_Texture *eLine1[12] = {NULL};
    enemy_set_texture(renderer, enemySkin[0], eLine1);
    SDL_Texture *eLine2[12] = {NULL};
    enemy_set_texture(renderer, enemySkin[1], eLine2);
    SDL_Texture *eLine3[12] = {NULL};
    enemy_set_texture(renderer, enemySkin[2], eLine3);
    
    //initializing alias bullets
    Uint32 prevBull_seconds = curr_seconds;
    loadMedia();
    Mix_PlayMusic( menuMusic, -1 );
    //MAIN MENU
    while (gameState == false){
        comeBack = false;
        SDL_GetMouseState(&Mx, &My);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_menu, NULL, NULL);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect Title;
        Title.x = 500;
        Title.y = 100;
        make_texture(renderer, "resource/img/TITLE.bmp", Title.x, Title.y, 500, 150, 1);
        SDL_Rect Start;
        Start.x = 600;
        Start.y = 350;
        Start.w = 500 * BUTTON_SIZE;
        Start.h = 150 * BUTTON_SIZE;
        if (!(Mx >= Start.x && Mx <= Start.x + Start.w && My >= Start.y && My <= Start.y + Start.h)) {
                make_texture(renderer, "resource/img/START_normal.bmp", Start.x, Start.y, 500, 150, BUTTON_SIZE);
        }
        else {
                make_texture(renderer, "resource/img/START_hover.bmp", Start.x, Start.y, 500, 150, BUTTON_SIZE);
        }

        SDL_Rect Score;
        Score.x = 575;
        Score.y = 495;
        Score.w = 500 * 0.7;
        Score.h = 150 * 0.7;
        if (!(Mx >= Score.x && Mx <= Score.x + Score.w && My >= Score.y && My <= Score.y + Score.h)) {
                make_texture(renderer, "resource/img/HIGHSCORE_normal.bmp", Score.x, Score.y, 500, 150, 0.7);
        }
        else {
                make_texture(renderer, "resource/img/HIGHSCORE_hover.bmp", Score.x, Score.y, 500, 150, 0.7);
        }


        SDL_Rect Exit;
        Exit.x = 600;
        Exit.y = 650;
        Exit.w = 500 * BUTTON_SIZE;
        Exit.h = 150 * BUTTON_SIZE;
        if (!(Mx >= Exit.x && Mx <= Exit.x + Exit.w && My >= Exit.y && My <= Exit.y + Exit.h)) {
                make_texture(renderer, "resource/img/EXIT_normal.bmp", Exit.x, Exit.y, 500, 150, BUTTON_SIZE);
        }
        else {
                make_texture(renderer, "resource/img/EXIT_hover.bmp", Exit.x, Exit.y, 500, 150, BUTTON_SIZE);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect Authors;
        Authors.x = 500;
        Authors.y = 850;
        make_texture(renderer, "resource/img/Authors.bmp", Authors.x, Authors.y, 500, 100, 1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                
        SDL_RenderPresent(renderer);
            while (SDL_PollEvent(&event) > 0) {
                switch (event.type) {
                case SDL_QUIT:
                        printf("Quitting application\n");
                        exit(0);
                        break;
                case SDL_MOUSEBUTTONDOWN:
                        switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                                if (Mx >= Start.x && Mx <= Start.x + Start.w && My >= Start.y && My <= Start.y + Start.h){
                                        gameState = true;
                                }
                                else if (Mx >= Score.x && Mx <= Score.x + Score.w && My >= Score.y && My <= Score.y + Score.h) {
                                        while(gameState == false) {
                                                if (comeBack)
                                                        break;
                                                SDL_GetMouseState(&Mx, &My);
                                                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
                                                SDL_RenderClear(renderer);
                                                SDL_RenderCopy(renderer, background_menu, NULL, NULL);
                                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                                make_texture(renderer, "resource/img/HIGHSCORE_normal.bmp", 515, 100, 500, 150, 1);
                                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                                                
                                                SDL_Surface* msg = TTF_RenderText_Solid(Pixel, "Press ESC to return", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
                                                SDL_Texture* msgT = SDL_CreateTextureFromSurface(renderer, msg); //now you can convert it into a texture
                                                SDL_FreeSurface(msg);
                                                SDL_Rect msgrect; //create a rect
                                                msgrect.x = 10;  //controls the rect's x coordinate 
                                                msgrect.y = 10; // controls the rect's y coordinte
                                                msgrect.w = 500; // controls the width of the rect
                                                msgrect.h = 80; // controls the height of the rect
                                                SDL_RenderCopy(renderer, msgT, NULL, &msgrect);
                                                SDL_DestroyTexture(msgT);

                                                SDL_Surface* score1 = TTF_RenderText_Solid(Pixel, "Oleg________________5280", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
                                                SDL_Texture* score1T = SDL_CreateTextureFromSurface(renderer, score1); //now you can convert it into a texture
                                                SDL_FreeSurface(score1);
                                                SDL_Rect score1rect; //create a rect
                                                score1rect.x = 425;  //controls the rect's x coordinate 
                                                score1rect.y = 300; // controls the rect's y coordinte
                                                score1rect.w = 700; // controls the width of the rect
                                                score1rect.h = 80; // controls the height of the rect
                                                SDL_RenderCopy(renderer, score1T, NULL, &score1rect);
                                                SDL_DestroyTexture(score1T);

                                                SDL_Surface* score2 = TTF_RenderText_Solid(Pixel, "Ihor________________4280", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
                                                SDL_Texture* score2T = SDL_CreateTextureFromSurface(renderer, score2); //now you can convert it into a texture
                                                SDL_FreeSurface(score2);
                                                SDL_Rect score2rect; //create a rect
                                                score2rect.x = 425;  //controls the rect's x coordinate 
                                                score2rect.y = 450; // controls the rect's y coordinte
                                                score2rect.w = 700; // controls the width of the rect
                                                score2rect.h = 80; // controls the height of the rect
                                                SDL_RenderCopy(renderer, score2T, NULL, &score2rect);
                                                SDL_DestroyTexture(score2T);
                                                
                                                SDL_Surface* score3 = TTF_RenderText_Solid(Pixel, "Vitalii________________2780", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
                                                SDL_Texture* score3T = SDL_CreateTextureFromSurface(renderer, score3); //now you can convert it into a texture
                                                SDL_FreeSurface(score3);
                                                SDL_Rect score3rect; //create a rect
                                                score3rect.x = 425;  //controls the rect's x coordinate 
                                                score3rect.y = 600; // controls the rect's y coordinte
                                                score3rect.w = 700; // controls the width of the rect
                                                score3rect.h = 80; // controls the height of the rect
                                                SDL_RenderCopy(renderer, score3T, NULL, &score3rect);
                                                SDL_DestroyTexture(score3T);

                                                SDL_RenderPresent(renderer);
                                                while (SDL_PollEvent(&event) > 0) {
                                                        switch (event.type) {
                                                                case SDL_QUIT:
                                                                        printf("Quitting application\n");
                                                                        exit(0);
                                                                        break;
                                                                case SDL_KEYDOWN:
                                                                switch (event.key.keysym.sym) {
                                                                        case 27:
                                                                        comeBack = true;
                                                                        break;
                                                                default:
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }

                                }
                                else if (Mx >= Exit.x && Mx <= Exit.x + Exit.w && My >= Exit.y && My <= Exit.y + Exit.h) {
                                        exit(0);
                                        break;
                        }
                        default:
                                break;
                }
        } 
    }
    }
    srand(time(NULL));
    while (gameState == true) {
        if (lives <= 0) {
                make_texture(renderer, "resource/img/GAME_OVER.bmp", 500, 400, 500, 150, 1);
                SDL_RenderPresent(renderer);
                usleep(3000000);
                exit(0);
        }
        else {
        char *scoreStr = mx_intToChar(score);
        SDL_Surface* surfaceScore = TTF_RenderText_Solid(Pixel, scoreStr, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
        SDL_Texture* textureScore = SDL_CreateTextureFromSurface(renderer, surfaceScore); //now you can convert it into a texture
        free(scoreStr);
        SDL_FreeSurface(surfaceScore);
        int max_bullets = rand() % (level * 5) + 1;
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
        SDL_RenderCopy(renderer, textureScore, NULL, &Score_rect);
        SDL_DestroyTexture(textureScore);

        if (enemy_count == 0) {
                enemies_init();
                level++;
                plane_fire_delay = 1;
                move_dist += 10;
                direction_movement += 20;
        }
        //draw all acitive bullets
        for (int a = 0; a < 10; a++)
        {
                if (boolets_exist[a])
                {
                        bul[a].y = bullet_logic(renderer, bul[a].x, bul[a].y, 1);
                        for (int i = 0; i < 3; i++)
                        {
                                for (int j = 0; j < 12; j++)
                                {
                                        if(enemyArray[i][j].isAlive && !enemyArray[i][j].damaged)
                                        if(bul[a].y == enemyArray[i][j].rect.y + 40 && (bul[a].x >= enemyArray[i][j].rect.x - 10 && bul[a].x <= enemyArray[i][j].rect.x + 40))
                                        {
                                                Mix_PlayChannel( -1, explousion, 0 );
                                                enemy_count--;
                                                score += 20;
                                                enemyArray[i][j].damaged = true;
                                                boolets_exist[a] = false;
                                        }
                                }
                        }
                }
        }

        //draw all active enemy bullets
        for (int i = 0; i < 20; i++) {
                if (enemy_boolets_exist[i]) {
                        ebul[i].y = eBullet_logic(renderer, ebul[i].x, ebul[i].y, -1);
                        if (isAlive) {
                                if (ebul[i].y == actor->y && (ebul[i].x >= actor->x && ebul[i].x <= actor->x + 80)) {
                                        enemy_boolets_exist[i] = false;
                                        count--;
                                        lives--;
                                        isAlive = false;   
                                }
                        }
                }
        }

        //draw all lives first, then the current actor
        for (int i = 0; i < lives - 1; i++) {
                make_texture(renderer, planeSkin[i + 1], planes[i].x, planes[i].y, 256, 256, LIVES_SIZE);
        }
        if (isAlive) {
                make_texture(renderer, planeSkin[skinIndex], actor->x, actor->y, 256, 256, ACTOR_SIZE);
                if (actor->x != plane_destination)
                        actor->x += plane_speed;
        }
        else {
                if (plane_death_timer == 0) {
                Mix_PlayChannel( -1, explousion, 0 );
                }
                death_anim(renderer, actor->x + 15, actor->y + 20, 191, 195, ACTOR_SIZE);
                if (plane_death_timer > 250) {
                        isAlive = true;
                        skinIndex = lives;
                        actor = &planes[lives - 1];
                        init_actor(actor);
                        plane_death_timer = 0;
                }
        }

        //draw all enemies
        for (int i = 0; i < 12; i++) {
                enemyArr_draw(renderer, eLine1[i], enemyArray[0], ENEMY_SIZE);
                enemyArr_draw(renderer, eLine2[i], enemyArray[1], ENEMY_SIZE);
                enemyArr_draw(renderer, eLine3[i], enemyArray[2], ENEMY_SIZE);
        }
        ticks = SDL_GetTicks();
        curr_seconds = ticks / 1000;
        bool changed = false;
        if (curr_seconds - prev_seconds >= 1) {
                for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 12; j++) {
                                if (enemyArray[i][j].isAlive && !enemyArray[i][j].damaged) {
                                        enemyArray[i][j].rect.x += direction_movement;
                                        if (enemyArray[i][j].rect.x > 1420) {
                                                direction_movement *= -1;
                                                for (int k = j; k >= 0; k--)
                                                        enemyArray[i][k].rect.x += direction_movement;
                                                changed = true;
                                                break;
                                        }
                                        if (enemyArray[i][j].rect.x < 20) {
                                                direction_movement *= -1;
                                                for (int k = j; k >= 0; k--)
                                                        enemyArray[i][k].rect.x += direction_movement;
                                                changed = true;
                                                break;
                                        }
                                }
                        }
                        if (count < max_bullets) {
                                int ind = rand() % 12;
                                if (enemyArray[i][ind].isAlive && !enemyArray[i][ind].damaged) {
                                        if (i < 2) {
                                                bool status = true;
                                                for (int j = i + 1; j <= 2; j++) {
                                                        if (enemyArray[j][ind].isAlive) {
                                                                status = false;
                                                                break;
                                                        }
                                                }
                                                if (status) {
                                                        int k = 0;
                                                        for (int p = 0; p < 20; p++) {
                                                                if (enemy_boolets_exist[p] == false) {
                                                                        k = p;
                                                                        break;
                                                                }
                                                        }
                                                        ebul[k].x = enemyArray[i][ind].rect.x + 20;
                                                        ebul[k].y = enemyArray[i][ind].rect.y + 40;
                                                        enemy_boolets_exist[k] = true;
                                                        count++;
                                                        Mix_PlayChannel( -1, enemy_shot, 0 );
                                                }
                                        }
                                        else {
                                                int k = 0;
                                                for (int p = 0; p < 20; p++) {
                                                        if (enemy_boolets_exist[p] == false) {
                                                                k = p;
                                                                break;
                                                        }
                                                }
                                                ebul[k].x = enemyArray[i][ind].rect.x + 20;
                                                ebul[k].y = enemyArray[i][ind].rect.y + 40;
                                                enemy_boolets_exist[k] = true;
                                                count++;
                                                Mix_PlayChannel( -1, enemy_shot, 0 );
                                        }
                                }
                        }
                        if (changed) {
                                break;
                        }
                }
                prev_seconds = curr_seconds;
        }

        
        SDL_RenderPresent(renderer);
        int j = 0;
        while (SDL_PollEvent(&event) > 0) {
                switch (event.type)
                {
                        case SDL_QUIT:
                                printf("Quitting application\n");
                                exit(0);
                                break;
                        case SDL_KEYDOWN:
                                switch (event.key.keysym.sym) {
                                        case 27:
                                                gameState = false;
                                                //PAUSE
                                                while(gameState == false){
                                                        SDL_GetMouseState(&Mx, &My);
                                                        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
                                                        SDL_RenderClear(renderer);
                                                        SDL_RenderCopy(renderer, background_menu, NULL, NULL);
                                                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                                        make_texture(renderer, "resource/img/PAUSE.bmp", 515, 100, 500, 150, 1);
                                                        
                                                        SDL_Rect Continue;
                                                        Continue.x = 575;
                                                        Continue.y = 350;
                                                        Continue.w = 500 * 0.7;
                                                        Continue.h = 150 * 0.7;
                                                        if (!(Mx >= Continue.x && Mx <= Continue.x + Continue.w && My >= Continue.y && My <= Continue.y + Continue.h)) {
                                                                make_texture(renderer, "resource/img/CONTINUE_normal.bmp", Continue.x, Continue.y, 500, 150, 0.7);
                                                        }
                                                        else {
                                                                make_texture(renderer, "resource/img/CONTINUE_hover.bmp", Continue.x, Continue.y, 500, 150, 0.7);
                                                        }
                                                        SDL_Rect Restart;
                                                        Restart.x = 600;
                                                        Restart.y = 550;
                                                        Restart.w = 500 * BUTTON_SIZE;
                                                        Restart.h = 150 * BUTTON_SIZE;
                                                        if (!(Mx >= Restart.x && Mx <= Restart.x + Restart.w && My >= Restart.y && My <= Restart.y + Restart.h)) {
                                                                make_texture(renderer, "resource/img/RESTART_normal.bmp", Restart.x, Restart.y, 500, 150, BUTTON_SIZE);
                                                        }
                                                        else {
                                                                make_texture(renderer, "resource/img/RESTART_hover.bmp", Restart.x, Restart.y, 500, 150, BUTTON_SIZE);
                                                        }
                                                        SDL_Rect Exit;
                                                        Exit.x = 600;
                                                        Exit.y = 750;
                                                        Exit.w = 500 * BUTTON_SIZE;
                                                        Exit.h = 150 * BUTTON_SIZE;
                                                        if (!(Mx >= Exit.x && Mx <= Exit.x + Exit.w && My >= Exit.y && My <= Exit.y + Exit.h)) {
                                                                make_texture(renderer, "resource/img/EXIT_normal.bmp", Exit.x, Exit.y, 500, 150, BUTTON_SIZE);
                                                        }
                                                        else {
                                                                make_texture(renderer, "resource/img/EXIT_hover.bmp", Exit.x, Exit.y, 500, 150, BUTTON_SIZE);
                                                        }
                                                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                                                        SDL_RenderPresent(renderer);
                                                        while (SDL_PollEvent(&event) > 0) {
                                                        switch (event.type)
                                                        {
                                                                case SDL_QUIT:
                                                                        printf("Quitting application\n");
                                                                        exit(0);
                                                                        break;
                                                                case SDL_MOUSEBUTTONDOWN:
                                                                        switch (event.button.button)
                                                                        {
                                                                        case SDL_BUTTON_LEFT:
                                                                                if (Mx >= Continue.x && Mx <= Continue.x + Continue.w && My >= Continue.y && My <= Continue.y + Continue.h){
                                                                                        gameState = true;
                                                                                }
                                                                                else if (Mx >= Exit.x && Mx <= Exit.x + Exit.w && My >= Exit.y && My <= Exit.y + Exit.h){
                                                                                        exit(0);
                                                                                }
                                                                                else if (Mx >= Restart.x && Mx <= Restart.x + Restart.w && My >= Restart.y && My <= Restart.y + Restart.h){
                                                                                        game_init();
                                                                                        usleep(20000);
                                                                                        gameState = true;
                                                                                }
                                                                                break;
                                                                        
                                                                        default:
                                                                                break;
                                                                        }
                                                        }
                                                        }
                                                }
                                                break;
                                        case 97:
                                                if (isAlive) {
                                                        plane_destination = actor->x - move_dist;
                                                        plane_speed = -1;
                                                        if(actor->x <= 0){
                                                                actor->x = 0;
                                                                plane_destination = 0;
                                                                break;
                                                        }
                                                }
                                                break;
                                        case 100:
                                                if (isAlive) {
                                                        plane_destination = actor->x + move_dist;
                                                        plane_speed = 1;
                                                        if(actor->x >= 1400){
                                                                plane_destination = 1400;
                                                                actor->x = 1400;
                                                                break;
                                                        }
                                                }
                                                break;
                                        case 32:
                                                if (curr_seconds - prevBull_seconds >= plane_fire_delay) {
                                                        Mix_PlayChannel( -1, plane_shot, 0 );
                                                        prevBull_seconds = curr_seconds;
                                                        for (int i = 0; i < 10; i++) {
                                                                if(boolets_exist[i] == false){
                                                                        j = i;
                                                                        break;
                                                                }
                                                        }
                                                        bul[j].x = actor->x + 40;
                                                        bul[j].y = actor->y - 20;
                                                        boolets_exist[j] = true;
                                                }
                                                break;
                                        default:
                                                break;
                                }
                        default:
                                break;
                }
        }
        for (int i = 0; i < 10; i++)
                        boolets_exist[i] = destroy(bul[i].y, boolets_exist[i]);
        for (int i = 0; i < 20; i++) {
                if (ebul[i].y >= 880 && enemy_boolets_exist[i])
                        count--;
                enemy_boolets_exist[i] = eBullet_destroy(ebul[i].y, enemy_boolets_exist[i]);
        }
    }
    }
    
    free(planes);
    Mix_FreeMusic( menuMusic );
    menuMusic = NULL;
    Mix_FreeChunk( plane_shot );
    plane_shot = NULL;
    Mix_FreeChunk( enemy_shot );
    enemy_shot = NULL;
    Mix_FreeChunk( explousion );
    explousion = NULL;
    SDL_DestroyTexture(bullet_texture);
    SDL_DestroyTexture(death_texture);
    SDL_DestroyTexture(background);
    for (int i = 0; i < 8; i++) {
            SDL_DestroyTexture(eLine1[i]);
            SDL_DestroyTexture(eLine2[i]);
            SDL_DestroyTexture(eLine3[i]);
    }
    SDL_DestroyTexture(gameOver);
    SDL_DestroyTexture(Message);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    SDL_Quit();
    if (argc && argv) {

    }
    return 0;
}
