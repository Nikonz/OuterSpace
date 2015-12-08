#include "../headers/CSurface.h"

CSurface::CSurface() {}

SDL_Surface* CSurface::OnLoad(char* File)
{
	SDL_Surface* Surf_Temp;

	Surf_Temp = SDL_LoadBMP(File);
	if (Surf_Temp == NULL) {
		printf("Loading BMP Failed: %s\n", SDL_GetError());
		return NULL;
	}

	return Surf_Temp;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y)
{
	if (Surf_Dest == NULL || Surf_Src == NULL) {
		printf("Surface Drawing failed: %s\n", SDL_GetError());
		return false;
	}
	else {
		SDL_Rect DestR;
		DestR.x = x;
		DestR.y = y;

		SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

		return true;
	}
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y, int x2, int y2, int w, int h)
{
	if (Surf_Dest == NULL || Surf_Src == NULL) {
		printf("Surface Drawing failed: %s\n", SDL_GetError());
		return false;
	}
	else {
		SDL_Rect DestR;
		DestR.x = x;
		DestR.y = y;

		SDL_Rect SrcR;
		SrcR.x = x2;
		SrcR.y = y2;
		SrcR.w = w;
		SrcR.h = h;

		SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

		return true;
	}
}

bool CSurface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B)
{
    if (Surf_Dest == NULL) {
        return false;
    }

    SDL_SetColorKey(Surf_Dest, SDL_TRUE, SDL_MapRGB(Surf_Dest->format, R, G, B));

    return true;
}

void CSurface::ClearSurface(SDL_Surface* Surf)
{
    if (Surf != NULL) {
        SDL_FreeSurface(Surf);
    }
}
