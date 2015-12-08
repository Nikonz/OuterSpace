#ifndef _CEVENT_H_
#define _CEVENT_H_

#include <SDL2/SDL.h>

class CEvent
{
	protected:
		CEvent();
		virtual ~CEvent();

		virtual void OnEvent(SDL_Event* Event);
		virtual void OnExit();
		virtual void OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
		virtual void OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
		virtual void OnMouseMove    (int mx, int my, int relx, int rely, bool Left, bool Right, bool Middle);
		virtual void OnLButtonDown  (int mx, int my);
		virtual void OnLButtonUp    (int mx, int my);
		virtual void OnRButtonDown  (int mx, int my);
		virtual void OnRButtonUp    (int mx, int my);
		virtual void OnMButtonDown  (int mx, int my);
		virtual void OnMButtonUp    (int mx, int my);
		virtual void OnMouseFocus();
		virtual void OnMouseBlur();
		virtual void OnInputFocus();
		virtual void OnInputBlur();
		virtual void OnWindowResized (int data1, int data2);
		virtual void OnJoyAxis          (Uint8 which, Uint8 axis, Sint16 value);
		virtual void OnJoyBall          (Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
		virtual void OnJoyHat           (Uint8 which, Uint8 hat, Uint8 button);
		virtual void OnJoyButtonDown    (Uint8 which, Uint8 button);
		virtual void OnJoyButtonUp      (Uint8 which, Uint8 button);
		virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
};

#endif
