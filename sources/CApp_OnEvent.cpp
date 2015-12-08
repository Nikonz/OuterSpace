#include "../headers/CApp.h"

void CApp::OnEvent(SDL_Event* Event)
{
	CEvent::OnEvent(Event);
}

void CApp::OnExit()
{
	Running = false;
}

void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode)
{
    switch (sym) {
        case SDLK_w: case SDLK_UP: {
            if (Mode == GAME || Mode == PAUSE) {
                Hero->MoveUp = true;
            }
            break;
        }
        case SDLK_s: case SDLK_DOWN: {
            if (Mode == GAME || Mode == PAUSE) {
                Hero->MoveDown = true;
            }
            break;
        }
        case SDLK_SPACE: {
            if (Mode == GAME || Mode == PAUSE) {
                Hero->FireOn = true;
            }
            break;
        }
        case SDLK_ESCAPE: {
            if (Mode == GAME) {
                if (!GameOver) {
                    Mode = PAUSE;
                } else {
                    Game_Music.Stop_Song();
                    Mode = MENU;
                }
            } else if (Mode == PAUSE) {
                if (!GameOver) {
                    Mode = GAME;
                }
            } else {
                Mode = MENU;
            }
            break;
        }
    }
}

void CApp::OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 scancode)
{
    switch (sym) {
        case SDLK_w: case SDLK_UP: {
            if (Mode == GAME || Mode == PAUSE) {
                Hero->MoveUp = false;
            }
            break;
        }
        case SDLK_s: case SDLK_DOWN: {
            if (Mode == GAME || Mode == PAUSE) {
                Hero->MoveDown = false;
            }
            break;
        }
        case SDLK_SPACE: {
            if (Mode == GAME || Mode == PAUSE) {
                Hero->FireOn = false;
            }
            break;
        }
    }
}

void CApp::OnMouseMove(int mx, int my, int relx, int rely, bool Left, bool Right, bool Middle)
{
	Cursor_X_Pos = mx;
	Cursor_Y_Pos = my;
}

void CApp::OnLButtonDown(int mx, int my)
{
    if (Mode == MENU || Mode == SETTINGS || Mode == SCORES) {
        Pressed_X_Pos = mx;
        Pressed_Y_Pos = my;
    }
}

void CApp::OnLButtonUp(int mx, int my)
{
    if (Mode == MENU) {
        if (Menu->Get_Button(0)->Active(mx, my) && Menu->Get_Button(0)->Active(Pressed_X_Pos, Pressed_Y_Pos)) {
            Mode = GAME;
            Menu_Music.Stop_Song();
            Init_Game();
        } else if (Menu->Get_Button(1)->Active(mx, my) && Menu->Get_Button(1)->Active(Pressed_X_Pos, Pressed_Y_Pos)) {
            Mode = SCORES;
        } else if (Menu->Get_Button(2)->Active(mx, my) && Menu->Get_Button(2)->Active(Pressed_X_Pos, Pressed_Y_Pos)) {
            Mode = SETTINGS;
        } else if (Menu->Get_Button(3)->Active(mx, my) && Menu->Get_Button(3)->Active(Pressed_X_Pos, Pressed_Y_Pos)) {
            OnExit();
        }
    } else if (Mode == SCORES) {
        if (Scores->Get_Button(0)->Active(mx, my) && Scores->Get_Button(0)->Active(Pressed_X_Pos, Pressed_Y_Pos)) {
            Mode = MENU;
        }
    } else if (Mode == SETTINGS) {
        if (Settings->Get_Button(0)->Active(mx, my) && Settings->Get_Button(0)->Active(Pressed_X_Pos, Pressed_Y_Pos)) {
            Mode = MENU;
        } else if (Settings->Get_CheckButton(0)->Active(mx, my) && Settings->Get_CheckButton(0)->Active(Pressed_X_Pos, Pressed_Y_Pos)) {
            Settings->Press_CheckButton(0);
            SoundsOn = !SoundsOn;
        } else if (Settings->Get_CheckButton(1)->Active(mx, my) && Settings->Get_CheckButton(1)->Active(Pressed_X_Pos, Pressed_Y_Pos)) {
            Settings->Press_CheckButton(1);
            MusicOn = !MusicOn;
            Menu_Music.Stop_Song();
        }
    }
    Pressed_X_Pos = -1;
    Pressed_Y_Pos = -1;
}
