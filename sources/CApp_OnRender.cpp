#include "../headers/CApp.h"

void CApp::OnRender()
{
    if (Mode == MENU) {
        CSurface::OnDraw(Surf_Screen, Surf_Background_Menu, 0, 0);
        RenderMenu(Menu);
    } else if (Mode == SCORES) {
        CSurface::OnDraw(Surf_Screen, Surf_Background_Scores, 0, 0);
        RenderMenu(Scores);
        for (int i = 0; i < Highscores.Get_Size(); i++) {
            CScore tmp = Highscores.Get_Score(i);
            char buf[22];
            sprintf(buf, "%d", (i + 1));
            CSurface::OnDraw(Surf_Screen, TTF_RenderText_Solid(Font_20, buf, Color_Blue), 100, 170 + i * 40);
            CSurface::OnDraw(Surf_Screen, TTF_RenderText_Solid(Font_20, tmp.Get_Name(), Color_Blue), 330, 170 + i * 40);
            sprintf(buf, "%d", tmp.Get_Score());
            CSurface::OnDraw(Surf_Screen, TTF_RenderText_Solid(Font_20, buf, Color_Blue), 560, 170 + i * 40);
        }
    } else if (Mode == SETTINGS) {
        CSurface::OnDraw(Surf_Screen, Surf_Background_Settings, 0, 0);
        RenderMenu(Settings);
    } else if (Mode == PAUSE) {
        SDL_Surface* Text = TTF_RenderText_Solid(Font_20, (char *)"PAUSE", ((Cur_Iteration / 50) % 2 ? Color_Orange : Color_Yellow));
        CSurface::OnDraw(Surf_Screen, Text, (WIDTH_DISPLAY - Text->w) / 2, (HEIGHT_DISPLAY - Text->h) / 2);
    } else {
        if (Background_W_Pos + WIDTH_DISPLAY <= Surf_Background->w) {
            CSurface::OnDraw(Surf_Screen, Surf_Background, 0, 0, Background_W_Pos, 0, WIDTH_DISPLAY, HEIGHT_DISPLAY);
        } else {
            CSurface::OnDraw(Surf_Screen, Surf_Background, 0, 0, Background_W_Pos, 0, (Surf_Background->w - Background_W_Pos), HEIGHT_DISPLAY);
            CSurface::OnDraw(Surf_Screen, Surf_Background,
                    (Surf_Background->w - Background_W_Pos), 0, 0, 0, WIDTH_DISPLAY - (Surf_Background->w - Background_W_Pos), HEIGHT_DISPLAY);
        }
        for (int i = 0; i < (int)Bullets.size(); i++) {
            CSurface::OnDraw(Surf_Screen, Bullets[i]->Get_Image(), Bullets[i]->Get_X(), Bullets[i]->Get_Y());
        }
        for (int i = 0; i < (int)Asteroids.size(); i++) {
            CSurface::OnDraw(Surf_Screen, Asteroids[i]->Get_Image(), Asteroids[i]->Get_X(), Asteroids[i]->Get_Y());
        }
        if (!GameOver) {
            CSurface::OnDraw(Surf_Screen, Hero->Get_Image(), Hero->Get_X(), Hero->Get_Y());
        }
        CSurface::OnDraw(Surf_Screen, Surf_HealthPanel,
            WIDTH_DISPLAY - Surf_HealthPanel->w * (1.0 * (Hero->Get_Health() + Slight_Health) / Hero->MAX_HEALTH) - 50,
            50, 0, 0, Surf_HealthPanel->w * (1.0 * (Hero->Get_Health() + Slight_Health) / Hero->MAX_HEALTH), Surf_HealthPanel->h);

        char Score_Panel[20];
        sprintf(Score_Panel, "SCORE %09d", Score);
        CSurface::OnDraw(Surf_Screen, TTF_RenderText_Solid(Font_20, Score_Panel, Color_Yellow), 50, 50);
        if (GameOver) {
            CSurface::OnDraw(Surf_Screen, Surf_GameOver, (WIDTH_DISPLAY - Surf_GameOver->w) / 2, (HEIGHT_DISPLAY - Surf_GameOver->h));
        }
	}
	SDL_UpdateWindowSurface(Surf_Display);
}

void CApp::RenderMenu(CMenu* Menu)
{
    for (int i = 0; i < Menu->Get_Size_Texts(); i++) {
        CText* text = Menu->Get_Texts(i);
        CSurface::OnDraw(Surf_Screen, text->Get_Image(), text->Get_X(), text->Get_Y());
    }
    for (int i = 0; i < Menu->Get_Size_Buttons(); i++) {
        CButton* button = Menu->Get_Button(i);
        CSurface::OnDraw(Surf_Screen, (!button->Active(Cursor_X_Pos, Cursor_Y_Pos) ? button->Get_Image() : button->Get_Image_Active()),
            button->Get_X(), button->Get_Y());
    }
    for (int i = 0; i < Menu->Get_Size_CheckButtons(); i++) {
        CCheck_Button* button = Menu->Get_CheckButton(i);
        CSurface::OnDraw(Surf_Screen, (!button->Active(Cursor_X_Pos, Cursor_Y_Pos) ? button->Get_Image() : button->Get_Image_Active()),
            button->Get_X(), button->Get_Y());
    }
}
