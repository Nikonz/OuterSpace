#include "../headers/CApp.h"

void CApp::OnMusic()
{
    if (Mode == MENU || Mode == SETTINGS || Mode == SCORES) {
        if (MusicOn && !Menu_Music.Playing()) {
            Menu_Music.Play_Song(Menu_Music.Next_Song());
        }
    } else {
        if (MusicOn && !Game_Music.Playing()) {
            Game_Music.Play_Song(Game_Music.Next_Song());
        }
    }
}
