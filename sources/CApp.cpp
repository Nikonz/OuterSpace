#include "../headers/CApp.h"

CApp::CApp()
{
	Surf_Display = NULL;

	Surf_Screen         = NULL;
	Surf_Background     = NULL;
	Surf_Hero           = NULL;
	Surf_HealthPanel    = NULL;
	Surf_Bullet         = NULL;
	Surf_GameOver       = NULL;
	Surf_Background_Menu = NULL;
	Surf_Button         = NULL;
	for (int i = 0; i < ASTEROID_TYPES; i++) {
        Surf_Asteroids[i] = NULL;
	}
	for (int i = 0; i < NUM_SHOOT_SOUNDS; i++) {
        Shoot_Sounds[i] = NULL;
	}
	Menu = NULL;
	Scores = NULL;
	Settings = NULL;
	Highscores = CHighscores(9);
	Font_20 = NULL;
	Font_30 = NULL;

    Color_Yellow.r = 225;
    Color_Yellow.g = 225;
    Color_Yellow.b = 0;
    Color_Yellow.a = 255;

    Color_Orange.r = 255;
    Color_Orange.g = 165;
    Color_Orange.b = 0;
    Color_Orange.a = 255;

    Color_Red.r = 220;
    Color_Red.g = 0;
    Color_Red.b = 0;
    Color_Red.a = 255;

    Color_Blue.r = 60;
    Color_Blue.g = 60;
    Color_Blue.b = 120;
    Color_Blue.a = 255;

    Cursor_X_Pos = -1;
    Cursor_Y_Pos = -1;
    Pressed_X_Pos = -1;
    Pressed_Y_Pos = -1;

	Running = true;
	Mode = MENU;
	SoundsOn = false;
	MusicOn = false;
	Hero = NULL;
}

CApp::~CApp() {};

int CApp::OnExecute()
{
	if  (OnInit() == false) {
        OnCleanup();
		return -1;
	}

	SDL_Event Event;
	steady_clock::time_point start_time = steady_clock::now();
	int next_game_iter = 0;
	while (Running) {
        OnMusic();
        for (int loops = 0; loops < MAX_FRAMESKIP; loops++, next_game_iter += MSEC_PER_ITER) {
            steady_clock::time_point cur_time = steady_clock::now();
            duration <double> dur_time = duration_cast <duration <double>> (cur_time - start_time);

            int dur = (int)(dur_time.count() * 1000);
            if (dur <= next_game_iter) {
                break;
            }

            while (SDL_PollEvent(&Event)) {
                OnEvent(&Event);
            }
            if (Mode == GAME) {
                OnLoop();
                Cur_Loop_Iteration++;
            }
            Cur_Iteration++;
        }
        OnRender();
	}
	FILE* Settings_File = fopen("data/settings", "w");
	fprintf(Settings_File, "%s\n%s\n", (char *)(SoundsOn ? "on" : "off"), (char *)(MusicOn ? "on" : "off"));
	fclose(Settings_File);
	Highscores.Load_to_File();
	OnCleanup();

	return 0;
}

int main( int argc, char** argv )
{
	CApp theApp;
	return theApp.OnExecute();
}
