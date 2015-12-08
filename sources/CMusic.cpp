#include "../headers/CMusic.h"

CMusic::CMusic()
{
    CurSong = 0;
    Songs.clear();
};

CMusic::~CMusic()
{
    for (int i = 0; i < (int)Songs.size(); i++) {
        Mix_FreeMusic(Songs[i]);
    }
    Songs.clear();
};

void CMusic::Add_Song(Mix_Music* Song)
{
    Songs.push_back(Song);
}

void CMusic::Play_Song(int num)
{
    Mix_FadeInMusic(Songs[num], 1, 500);
}

void CMusic::Stop_Song()
{
    Mix_FadeOutMusic(100);
}

void CMusic::ReShuffle()
{
    random_shuffle(Songs.begin(), Songs.end());
}

int CMusic::Next_Song()
{
    return CurSong = (CurSong + 1) % Songs.size();
}

bool CMusic::Playing()
{
    return (bool)Mix_PlayingMusic();
}
