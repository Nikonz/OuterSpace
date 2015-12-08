#ifndef _CSURFACE_H_
#define _CSURFACE_H_

#include<SDL2/SDL.h>

class CSurface
{
	public:
		CSurface();
	public:
		static SDL_Surface* OnLoad( char* File );

		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y);
		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y, int x2, int y2, int w, int h);
		static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
		static void ClearSurface(SDL_Surface* Surf);
};

#endif

