#include "../headers/CMenu.h"

/// ======== CText =========

CText::CText(int x, int y, SDL_Surface* image)
{
    X_pos = x;
    Y_pos = y;
    Image = image;
    W = (image == NULL ? -1 : image->w);
    H = (image == NULL ? -1 : image->h);
}

CText::~CText()
{
    delete Image;
};

int CText::Get_X()
{
    return X_pos;
}

int CText::Get_Y()
{
    return Y_pos;
}

SDL_Surface* CText::Get_Image()
{
    return Image;
}

/// ======= CButton ========

CButton::CButton(int x, int y, SDL_Surface* image, SDL_Surface* image_active)
{
    X_pos = x;
    Y_pos = y;
    Image = image;
    Image_Active = image_active;
    W = (image == NULL ? -1 : image->w);
    H = (image == NULL ? -1 : image->h);
}

CButton::~CButton()
{
    delete Image_Active;
};

bool CButton::Active(int cursor_x, int cursor_y)
{
    return (X_pos <= cursor_x && cursor_x <= X_pos + W && Y_pos <= cursor_y && cursor_y <= Y_pos + H);
}

SDL_Surface* CButton::Get_Image_Active()
{
    return Image_Active;
}

/// ==== CCheck_Button ====

CCheck_Button::CCheck_Button(int x, int y, SDL_Surface* image, SDL_Surface* image_active, SDL_Surface* image2, SDL_Surface* image2_active)
{
    X_pos = x;
    Y_pos = y;
    Image = image;
    Image2 = image2;
    Image_Active = image_active;
    Image2_Active = image2_active;
    W = (image == NULL ? -1 : image->w);
    H = (image == NULL ? -1 : image->h);
}

CCheck_Button::~CCheck_Button()
{
    delete Image2;
    delete Image2_Active;
};

void CCheck_Button::Press()
{
    swap(Image, Image2);
    swap(Image_Active, Image2_Active);
    W = (Image == NULL ? -1 : Image->w);
    H = (Image == NULL ? -1 : Image->h);
}

/// ======= CMenu ========

CMenu::CMenu()
{
    Buttons.clear();
    Check_Buttons.clear();
    Texts.clear();
};

CMenu::~CMenu()
{
    for (int i = 0; i < (int)Buttons.size(); i++) {
        delete Buttons[i];
    }
    Buttons.clear();
    for (int i = 0; i < (int)Check_Buttons.size(); i++) {
        delete Check_Buttons[i];
    }
    Check_Buttons.clear();
    for (int i = 0; i < (int)Texts.size(); i++) {
        delete Texts[i];
    }
    Texts.clear();
};

void CMenu::Add_Button(CButton* button)
{
    Buttons.push_back(button);
}

void CMenu::Add_CheckButton(CCheck_Button* button)
{
    Check_Buttons.push_back(button);
}

void CMenu::Add_Text(CText* text)
{
    Texts.push_back(text);
}

void CMenu::Press_CheckButton(int ind)
{
    Check_Buttons[ind]->Press();
}

CButton* CMenu::Get_Button(int ind)
{
    return Buttons[ind];
}

CCheck_Button* CMenu::Get_CheckButton(int ind)
{
    return Check_Buttons[ind];
}

CText* CMenu::Get_Texts(int ind)
{
    return Texts[ind];
}

int CMenu::Get_Size_Buttons()
{
    return Buttons.size();
}

int CMenu::Get_Size_CheckButtons()
{
    return Check_Buttons.size();
}

int CMenu::Get_Size_Texts()
{
    return Texts.size();
}
