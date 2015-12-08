#include "../headers/CApp.h"

void CApp::OnCleanup()
{
    ClearObjects();
    CSurface::ClearSurface(Surf_Background);
    CSurface::ClearSurface(Surf_Background_Menu);
    CSurface::ClearSurface(Surf_Background_Settings);
    CSurface::ClearSurface(Surf_Background_Scores);
    CSurface::ClearSurface(Surf_Button);
    CSurface::ClearSurface(Surf_Hero);
    CSurface::ClearSurface(Surf_Screen);
    CSurface::ClearSurface(Surf_Bullet);
    CSurface::ClearSurface(Surf_HealthPanel);
    CSurface::ClearSurface(Surf_GameOver);
    TTF_CloseFont(Font_20);
    TTF_CloseFont(Font_30);
    for (int i = 0; i < ASTEROID_TYPES; i++) {
        CSurface::ClearSurface(Surf_Asteroids[i]);
    }
    for (int i = 0; i < NUM_SHOOT_SOUNDS; i++) {
        Mix_FreeChunk(Shoot_Sounds[i]);
	}
    Mix_CloseAudio();
    delete Menu;
    delete Scores;
    delete Settings;
    Highscores.Close_File();

    if (Surf_Display != NULL) {
        SDL_DestroyWindow(Surf_Display);
	}
	SDL_Quit();
}

void CApp::ClearObjects()
{
    for (int i = 0; i < (int)Bullets.size(); i++) {
        delete Bullets[i];
    }
    for (int i = 0; i < (int)Asteroids.size(); i++) {
        delete Asteroids[i];
    }
    Bullets.clear();
    Asteroids.clear();
    if (Hero != NULL) {
        delete Hero;
        Hero = NULL;
    }
}
