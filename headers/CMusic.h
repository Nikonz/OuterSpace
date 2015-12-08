#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <SDL2/SDL_mixer.h>
#include <algorithm>

using std::vector;

class CMusic
{
    private:
        vector <Mix_Music*> Songs;
        int CurSong;
    public:
        CMusic();
        virtual ~CMusic();

        void Add_Song(Mix_Music* Song);
        void Play_Song(int num);
        void Stop_Song();
        void ReShuffle();
        bool Playing();
        int Next_Song();
};

#endif // _MUSIC_H_
