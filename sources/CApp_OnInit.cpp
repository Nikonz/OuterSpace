#include "../headers/CApp.h"

bool CApp::OnInit()
{
    srand(time(NULL));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return false;
	}
	Surf_Display = SDL_CreateWindow(
        "Outer Space",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH_DISPLAY,
        HEIGHT_DISPLAY,
        !SDL_WINDOW_RESIZABLE
        );

	if (Surf_Display == NULL) {
		printf("Creating Window failed: %s\n", SDL_GetError());
		return false;
	} else {
		Surf_Screen = SDL_GetWindowSurface(Surf_Display);
	}

	if (!Init_Images() || !Init_Audio() || !Init_Fonts() || !Init_Menu()) {
        return false;
    }

	return true;
}

void CApp::Init_Game()
{
    ClearObjects();
    GameOver = false;
    Score = 0;
    Background_W_Pos = 0;
    Slight_Health = 0;
    Cur_Loop_Iteration = 0;
    Cur_Iteration = 0;
	Hero = new CHero(WIDTH_DISPLAY / 20, HEIGHT_DISPLAY / 2, 0, -2.0, HEIGHT_DISPLAY, 0, 0, WIDTH_DISPLAY, 100, 0.4 * ITER_PER_SEC / GAME_SPEED, 10);
	Hero->Append_Image(Surf_Hero);
	Gravity = 9.0 * GAME_SPEED / ITER_PER_SEC;
	Acceleration = 27.0 * GAME_SPEED / ITER_PER_SEC;
	Add_Speed = 0.0;
}

bool CApp::Init_Menu()
{
    SDL_Surface* text;
    SDL_Surface* text2;
    SDL_Surface* text_active;
    SDL_Surface* text_active2;

    Menu = new CMenu();
    Scores = new CMenu();
    Settings = new CMenu();

    text        = TTF_RenderText_Solid(Font_30, (char *)"Start", Color_Yellow);
    text_active = TTF_RenderText_Solid(Font_30, (char *)"Start", Color_Orange);
    Menu->Add_Button(new CButton((WIDTH_DISPLAY - text->w) / 2, 200, text, text_active));

    text        = TTF_RenderText_Solid(Font_30, (char *)"Highscores", Color_Yellow);
    text_active = TTF_RenderText_Solid(Font_30, (char *)"Highscores", Color_Orange);
    Menu->Add_Button(new CButton((WIDTH_DISPLAY - text->w) / 2, 250, text, text_active));

    text        = TTF_RenderText_Solid(Font_30, (char *)"Settings", Color_Yellow);
    text_active = TTF_RenderText_Solid(Font_30, (char *)"Settings", Color_Orange);
    Menu->Add_Button(new CButton((WIDTH_DISPLAY - text->w) / 2, 300, text, text_active));

    text        = TTF_RenderText_Solid(Font_30, (char *)"Quit", Color_Yellow);
    text_active = TTF_RenderText_Solid(Font_30, (char *)"Quit", Color_Orange);
    Menu->Add_Button(new CButton((WIDTH_DISPLAY - text->w) / 2, 350, text, text_active));

    text        = TTF_RenderText_Solid(Font_20, (char *)"Back", Color_Yellow);
    text_active = TTF_RenderText_Solid(Font_20, (char *)"Back", Color_Orange);
    Scores->Add_Button(new CButton(50, 50, text, text_active));

    text        = TTF_RenderText_Solid(Font_20, (char *)"Back", Color_Yellow);
    text_active = TTF_RenderText_Solid(Font_20, (char *)"Back", Color_Orange);
    Settings->Add_Button(new CButton(50, 50, text, text_active));

    text         = TTF_RenderText_Solid(Font_30, (char *)"On", Color_Yellow);
    text2        = TTF_RenderText_Solid(Font_30, (char *)"Off", Color_Yellow);
    text_active  = TTF_RenderText_Solid(Font_30, (char *)"On", Color_Orange);
    text_active2 = TTF_RenderText_Solid(Font_30, (char *)"Off", Color_Orange);
    Settings->Add_CheckButton(new CCheck_Button(500, 230, text, text_active, text2, text_active2));

    text         = TTF_RenderText_Solid(Font_30, (char *)"On", Color_Yellow);
    text2        = TTF_RenderText_Solid(Font_30, (char *)"Off", Color_Yellow);
    text_active  = TTF_RenderText_Solid(Font_30, (char *)"On", Color_Orange);
    text_active2 = TTF_RenderText_Solid(Font_30, (char *)"Off", Color_Orange);
    Settings->Add_CheckButton(new CCheck_Button(500, 330, text, text_active, text2, text_active2));

    text    = TTF_RenderText_Solid(Font_30, (char *)"Sounds", Color_Yellow);
    text2   = TTF_RenderText_Solid(Font_30, (char *)"Music", Color_Yellow);
    Settings->Add_Text(new CText(100, 230, text));
    Settings->Add_Text(new CText(100, 330, text2));

    text = TTF_RenderText_Solid(Font_20, (char *)"Place", Color_Red);
    Scores->Add_Text(new CText(100, 120, text));
    text = TTF_RenderText_Solid(Font_20, (char *)"Name", Color_Red);
    Scores->Add_Text(new CText(330, 120, text));
    text = TTF_RenderText_Solid(Font_20, (char *)"Result", Color_Red);
    Scores->Add_Text(new CText(560, 120, text));

    if (!SoundsOn) {
        Settings->Press_CheckButton(0);
    }
    if (!MusicOn) {
        Settings->Press_CheckButton(1);
    }

    if (Highscores.Append_File((char *)"data/highscores") == -1) {
        return false;
    }
    Highscores.Load_from_File();

    return true;
}

bool CApp::Init_Fonts()
{
    if (TTF_Init()) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        return false;
    }
    Font_20 = TTF_OpenFont("fonts/8-BIT.TTF", 20);
    Font_30 = TTF_OpenFont("fonts/8-BIT.TTF", 30);
    if (Font_20 == NULL || Font_30 == NULL) {
        printf("Loading font failed: %s\n", TTF_GetError());
        return false;
    }
    return true;
}

bool CApp::Init_Images()
{
    Surf_Background_Menu =      CSurface::OnLoad((char *)"images/Asteroids_Background1.bmp");
    Surf_Background_Settings =  CSurface::OnLoad((char *)"images/Asteroids_Background2.bmp");
    Surf_Background_Scores =    CSurface::OnLoad((char *)"images/Asteroids_Background3.bmp");
    Surf_Background =   CSurface::OnLoad((char *)"images/Space_Background3.bmp");
	Surf_Hero =         CSurface::OnLoad((char *)"images/jetpack.bmp");
	Surf_HealthPanel =  CSurface::OnLoad((char *)"images/health_panel.bmp");
	Surf_Bullet =       CSurface::OnLoad((char *)"images/bullet.bmp");
	Surf_GameOver =     CSurface::OnLoad((char *)"images/game-over.bmp");
	if (Surf_Background == NULL || Surf_Hero == NULL
        || Surf_HealthPanel == NULL || Surf_Bullet == NULL
        || Surf_GameOver == NULL || Surf_Background_Menu == NULL) {
		printf("Loading Images failed: %s\n", SDL_GetError());
		return false;
	}

	for (int i = 0; i < ASTEROID_TYPES; i++) {
        char tmp[21] = "images/asteroidX.bmp";
        tmp[15] = char('0' + i + 1);
        Surf_Asteroids[i] = CSurface::OnLoad(tmp);
        if (Surf_Asteroids[i] == NULL) {
            printf("Loading Images failed: %s\n", SDL_GetError());
            return false;
        }
        CSurface::Transparent(Surf_Asteroids[i], 0, 0, 0);
	}
	CSurface::Transparent(Surf_Hero, 0, 0, 0);
	CSurface::Transparent(Surf_HealthPanel, 0, 0, 0);
	CSurface::Transparent(Surf_Bullet, 0, 0, 0);
	CSurface::Transparent(Surf_GameOver, 0, 0, 0);

	return true;
}
bool CApp::Init_Audio()
{
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);

    FILE* Settings_File = fopen("data/settings", "r");
    if (Settings_File == NULL) {
        printf("Cannot open data/settings\n");
        return false;
    }
    char sounds[5], music[5];
    fscanf(Settings_File, "%s\n%s", sounds, music);
    SoundsOn = ((std::string)sounds == (char *)"on");
    MusicOn = ((std::string)music == (char *)"on");
    fclose(Settings_File);

    for (int i = 0; i < NUM_SHOOT_SOUNDS; i++) {
        char tmp[23] = "audio/samples/gunX.wav";
        tmp[17] = char('0' + i + 1);
        Shoot_Sounds[i] = Mix_LoadWAV(tmp);
        if(Shoot_Sounds[i] == NULL) {
            printf("Mix_LoadWAV Failed: %s\n", Mix_GetError());
            return false;
        }
    }
    Mix_AllocateChannels(2);
    Mix_Volume(0, 80);
    Mix_Volume(1, 80);

    for (int i = 0; i < NUM_MENU_SONGS; i++) {
        char tmp[22] = "audio/music/MenuX.mp3";
        tmp[16] = char('0' + i + 1);
        Mix_Music *music = Mix_LoadMUS(tmp);
        if (music == NULL) {
            printf("Loading Audio failed: %s\n", Mix_GetError());
            return false;
        } else {
            Menu_Music.Add_Song(music);
        }
    }

    for (int i = 0; i < NUM_GAME_SONGS; i++) {
        char tmp[23] = "audio/music/ThemeX.mp3";
        tmp[17] = char('0' + i + 1);
        Mix_Music *music = Mix_LoadMUS(tmp);
        if (music == NULL) {
            printf("Loading Audio failed: %s\n", Mix_GetError());
            return false;
        } else {
            Game_Music.Add_Song(music);
        }
    }

    Game_Music.ReShuffle();

    return true;
}
