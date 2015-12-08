#ifndef _CAPP_H_
#define _CAPP_H_

#include <ctime>
#include <unistd.h>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "CEvent.h"
#include "CSurface.h"
#include "CObjects.h"
#include "CMacros.h"
#include "CMusic.h"
#include "CMenu.h"
#include "CHighscores.h"
#include <vector>
#include <chrono>

using namespace std::chrono;
using std::vector;
using std::cout;
using std::endl;

#define MENU 0
#define SCORES 1
#define SETTINGS 2
#define GAME 3
#define PAUSE 4

class CApp : public CEvent
{
	private:
        static const int ITER_PER_SEC = 100;
        static const int MSEC_PER_ITER = 1000 / ITER_PER_SEC;
        static const int MAX_FRAMESKIP = 5;
        static const int HEIGHT_DISPLAY = 600;
		static const int WIDTH_DISPLAY = 800;

		static const int ASTEROID_TYPES = 3;
		const int ASTEROIDS_HEALTH[(int)ASTEROID_TYPES] = {10, 20, 30};
		const int ASTEROIDS_DAMAGE[(int)ASTEROID_TYPES] = {4, 7, 10};
		const int ASTEROIDS_COST[(int)ASTEROID_TYPES] = {600, 800, 1000};

		static const int NUM_GAME_SONGS = 2;
		static const int NUM_MENU_SONGS = 1;
		static const int NUM_SHOOT_SOUNDS = 3;
		static const int NUM_HIGHSCORES = 5;

		Mix_Chunk* Shoot_Sounds[NUM_SHOOT_SOUNDS];
        CMusic Game_Music;
        CMusic Menu_Music;
        CMenu *Menu;
        CMenu *Scores;
        CMenu *Settings;
        CHighscores Highscores;

        int Cursor_X_Pos;
        int Cursor_Y_Pos;
        int Pressed_X_Pos;
        int Pressed_Y_Pos;

		bool Running;
		bool GameOver;
		bool SoundsOn;
		bool MusicOn;
		char Mode;
		SDL_Window* Surf_Display;
		SDL_Surface* Surf_Background;
		SDL_Surface* Surf_Background_Menu;
		SDL_Surface* Surf_Background_Settings;
		SDL_Surface* Surf_Background_Scores;
		SDL_Surface* Surf_Button;
		SDL_Surface* Surf_GameOver;
		SDL_Surface* Surf_Hero;
		SDL_Surface* Surf_Screen;
		SDL_Surface* Surf_HealthPanel;
		SDL_Surface* Surf_Bullet;
		SDL_Surface* Surf_Asteroids[ASTEROID_TYPES];
		TTF_Font *Font_20;
		TTF_Font *Font_30;
		SDL_Color Color_Yellow;
		SDL_Color Color_Orange;
		SDL_Color Color_Red;
		SDL_Color Color_Blue;
		double Background_W_Pos;
		int Slight_Health;

        static constexpr double GAME_SPEED = 1.0; // Easy = 0.6, Normal = 1.0, Hard = 1.7, Survival = 2.5
        static const int ITER_BETWEEN_GEN_ASTEROIDS = 50 / GAME_SPEED;
        double Add_Speed;
        double Gravity;
        double Acceleration;

        CHero* Hero;
        int Cur_Iteration;
		int Cur_Loop_Iteration;
		vector <CBullet*> Bullets;
		vector <CAsteroid*> Asteroids;

		int Score;
    private:
        bool OnInit();
		bool Init_Images();
		bool Init_Audio();
		bool Init_Fonts();
        bool Init_Menu();
        void Init_Game();
        void OnLoop();
		void OnRender();
		void RenderMenu(CMenu* Menu);
		void OnMusic();
		void OnCleanup();
		void ClearObjects();
        void OnEvent(SDL_Event *Event);
        void OnMouseMove(int mx, int my, int relx, int rely, bool Left, bool Right, bool Middle);
        void OnLButtonDown(int mx, int my);
        void OnLButtonUp(int mx, int my);
		void OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
		void OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
		void OnExit();
	public:
		CApp();
		virtual ~CApp();
		int OnExecute();
};

#endif
