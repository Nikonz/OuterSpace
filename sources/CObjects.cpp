#include "../headers/CObjects.h"

/// =========== CObject ===========

CObject::CObject() {}

CObject::~CObject() {}

void CObject::Append_Image(SDL_Surface* Surf_Image)
{
    Image = Surf_Image;
    H = (Image == NULL ? -1 : Image->h);
    W = (Image == NULL ? -1 : Image->w);
}

SDL_Surface* CObject::Get_Image()
{
    return Image;
}

int CObject::Get_H()
{
    return H;
}

int CObject::Get_W()
{
    return W;
}

int CObject::Get_X()
{
    return (int)X_pos;
}

int CObject::Get_Y()
{
    return (int)Y_pos;
}

int CObject::Get_UpBound()
{
    return (int)UpBound;
}

int CObject::Get_LowBound()
{
    return (int)LowBound;
}

int CObject::Get_LeftBound()
{
    return (int)LeftBound;
}

int CObject::Get_RightBound()
{
    return (int)RightBound;
}

int CObject::Get_Health()
{
    return Health;
}

void CObject::Inc_Speed(double x, double y)
{
    V_x += x;
    V_y += y;
}

void CObject::Dec_Health(int x)
{
    Health -= x;
    Health = max(Health, 0);
}

void CObject::Make_Dead()
{
    Health = 0;
}

void CObject::Move()
{
    X_pos += V_x;
    Y_pos += V_y;
    if (Y_pos < LowBound - Image->h) {
        Y_pos = LowBound - Image->h;
        V_y = 0;
    } else if (Y_pos > UpBound) {
        Y_pos = UpBound;
        V_y = 0;
    }
    if (X_pos < LeftBound - Image->w) {
        X_pos = LeftBound - Image->w;
        V_x = 0;
    } else if (X_pos > RightBound) {
        X_pos = RightBound;
        V_x = 0;
    }
}

/// =========== CBullet ===========

CBullet::CBullet(double x, double y, double vx, double vy, int damage,
            int health, int upBound, int lowBound, int leftBound, int rightBound)
{
    Health = health;
    X_pos = x;
    Y_pos = y;
    V_x = vx;
    V_y = vy;
    Damage = damage;
    UpBound = upBound;
    LowBound = lowBound;
    LeftBound = leftBound;
    RightBound = rightBound;
}

CBullet::~CBullet() {}

int CBullet::Get_Damage()
{
    return Damage;
}

bool CBullet::Need_to_Destroy()
{
    if (X_pos == LeftBound - Image->w || X_pos == RightBound || Y_pos == LowBound - Image->h || Y_pos == UpBound
        || Health == 0) {
        //printf("%.2f %.2f %d\n", X_pos, Y_pos, Health);
        return true;
    } else {
        return false;
    }
}

/// =========== CAsteroid ===========

CAsteroid::CAsteroid(int width, int height, double speed_lim_x, double speed_lim_y, double variat,
                    int damage, int health, int cost, SDL_Surface* image)
{
    Image = image;
    H = image->h;
    W = image->w;
    LowBound = 0;
    LeftBound = 0;
    RightBound = width;
    UpBound = height;

    Health = health;
    Damage = damage;
    Cost = cost;

    V_x = -rand() % (int)(speed_lim_x * 500) / 1000.0 - 0.5 * speed_lim_x;
    V_y =  rand() % (int)(speed_lim_y * 500) / 1000.0 + 0.5 * speed_lim_y;

    X_pos = width;
    Y_pos = -H + (H + height) * (variat * rand() / RAND_MAX);
}

CAsteroid::~CAsteroid() {}

int CAsteroid::Get_Cost()
{
    return Cost;
}

/// =========== CHero ===========

CHero::CHero(double x, double y, double vx, double vy,
            int upBound, int lowBound, int leftBound, int rightBound,
            int health, int fire_delay, int bullet_damage)
{
    MoveUp = false;
    MoveDown = false;
    FireOn = false;
    Fire_Delay = fire_delay;
    Fire_Last = -fire_delay;
	Bullet_Damage = bullet_damage;

    X_pos = x;
    Y_pos = y;
    V_x = vx;
    V_y = vy;
    Health = health;
    UpBound = upBound;
    LowBound = lowBound;
    LeftBound = leftBound;
    RightBound = rightBound;
}

CHero::~CHero() {}

void CHero::Inc_Health(int x)
{
    Health += x;
    Health = max(Health, (int)MAX_HEALTH);
}

bool CHero::Can_Shoot(int iter)
{
    return (Fire_Last + Fire_Delay <= iter);
}

CBullet* CHero::Shoot(int iter, SDL_Surface* Surf, double speed)
{
    CBullet* bullet = new CBullet(X_pos + W / 2 - Surf->w / 2,
                                Y_pos + H / 3 - Surf->h / 2,
                                speed, 0, Bullet_Damage, 1,
                                UpBound, LowBound, LeftBound, RightBound);
    bullet->Append_Image(Surf);
    Fire_Last = iter;
    return bullet;
}
