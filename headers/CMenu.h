#ifndef _CMENU_H_
#define _CMENU_H_

#include <SDL2/SDL.h>
#include <vector>

using std::vector;
using std::swap;

class CText
{
    protected:
        SDL_Surface* Image;
        int X_pos;
        int Y_pos;
        int H;
        int W;
    public:
        CText(int x = 0, int y = 0, SDL_Surface* image = NULL);
        virtual ~CText();

        SDL_Surface* Get_Image();
        int Get_X();
        int Get_Y();
};

class CButton : public CText
{
    protected:
        SDL_Surface* Image_Active;
    public:
        CButton(int x = 0, int y = 0, SDL_Surface* image = NULL, SDL_Surface* image_active = NULL);
        virtual ~CButton();

        bool Active(int cursor_x, int cursor_y);
        SDL_Surface* Get_Image_Active();
};

class CCheck_Button : public CButton
{
    protected:
        SDL_Surface* Image2;
        SDL_Surface* Image2_Active;
    public:
        CCheck_Button(int x = 0,
                    int y = 0,
                    SDL_Surface* image = NULL,
                    SDL_Surface* image_active = NULL,
                    SDL_Surface* image2 = NULL,
                    SDL_Surface* image2_active = NULL);
        virtual ~CCheck_Button();

        void Press();
};

class CMenu
{
    private:
        vector <CButton*> Buttons;
        vector <CCheck_Button*> Check_Buttons;
        vector <CText*> Texts;
    public:
        CMenu();
        virtual ~CMenu();

        CButton*          Get_Button(int ind);
        CCheck_Button*    Get_CheckButton(int ind);
        CText*            Get_Texts(int ind);
        void        Add_Button(CButton* button);
        void        Add_CheckButton(CCheck_Button* button);
        void        Add_Text(CText* text);
        void        Press_CheckButton(int ind);
        int         Get_Size_Buttons();
        int         Get_Size_CheckButtons();
        int         Get_Size_Texts();
};

#endif // _CMENU_H_
