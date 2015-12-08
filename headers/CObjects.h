#ifndef _CCHARACTERS_H_
#define _CCHARACTERS_H_

#include <SDL2/SDL.h>
#include <algorithm>

using std::max;
using std::min;

class CObject
{
    protected:
        SDL_Surface* Image;
        int H;
        int W;

        double X_pos;
        double Y_pos;
        double V_x;
        double V_y;

        int Health;

        int UpBound;
        int LowBound;
        int LeftBound;
        int RightBound;
    public:
        CObject();
        virtual ~CObject();

        void            Append_Image(SDL_Surface* Surf_Image);
        SDL_Surface*    Get_Image();
        int             Get_H();
        int             Get_W();

        int             Get_X();
        int             Get_Y();
        int             Get_UpBound();
        int             Get_LowBound();
        int             Get_LeftBound();
        int             Get_RightBound();
        int             Get_Health();

        void            Inc_Speed(double x, double y);
        void            Dec_Health(int x);
        void            Make_Dead();
        void            Move();
};

class CBullet : public CObject
{
    protected:
        int Damage;
    public:
        CBullet (double x = 0,
                double y = 0,
                double vx = 0,
                double vy = 0,
                int damage = 0,
                int health = 0,
                int upBound = 0,
                int lowBound = 0,
                int leftBound = 0,
                int rightBound = 0);
        virtual ~CBullet();

        bool Need_to_Destroy();
        int Get_Damage();
};

class CAsteroid : public CBullet
{
    private:
        int Cost;
    public:
        CAsteroid (int width = 0,
                    int height = 0,
                    double speed_lim_x = 0,
                    double speed_lim_y = 0,
                    double variat = 0,
                    int damage = 0,
                    int health = 0,
                    int cost = 0,
                    SDL_Surface* image = NULL);
        virtual ~CAsteroid();

        int Get_Cost();
};

class CHero : public CObject
{
    private:
        int Fire_Delay;
        int Fire_Last;
		int Bullet_Damage;
    public:
        static const int MAX_HEALTH = 100;
        bool MoveUp;
		bool MoveDown;
		bool FireOn;
        CHero  (double x = 0,
                double y = 0,
                double vx = 0,
                double vy = 0,
                int upBound = 0,
                int lowBound = 0,
                int leftBound = 0,
                int rightBound = 0,
                int health = 0,
                int fire_delay = 0,
                int bullet_damage = 0);
        virtual ~CHero();

        void        Inc_Health(int x);
        bool        Can_Shoot(int iter);
        CBullet*    Shoot(int iter, SDL_Surface* Surf, double speed);
};

#endif // _CCHARACTERS_H_
