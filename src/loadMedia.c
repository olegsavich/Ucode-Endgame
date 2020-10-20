#include "../inc/header.h"

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    //Load music
    menuMusic = Mix_LoadMUS( "resource/music/music.wav" );
    if( menuMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    plane_shot = Mix_LoadWAV( "resource/music/plane_shot.wav" );
    if( plane_shot == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    enemy_shot = Mix_LoadWAV( "resource/music/enemy_shot.wav" );
    if( plane_shot == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    explousion = Mix_LoadWAV( "resource/music/explousion.wav" );
    if( plane_shot == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    return success;
}
