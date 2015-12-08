#include "../headers/CApp.h"

bool Intersection(CObject First, CObject Second);

void CApp::OnLoop()
{
    if (!GameOver) {
        Score++;
    }
    Background_W_Pos += ((GAME_SPEED + Add_Speed) / 3);
    if (Background_W_Pos >= Surf_Background->w) {
        Background_W_Pos -= Surf_Background->w;
    }

    if (Hero->Get_Y() >= Hero->Get_UpBound() - Hero->Get_H() || Hero->Get_Y() <= Hero->Get_LowBound()) {
        Hero->Dec_Health(1);
    }
    Hero->Inc_Speed(0, Gravity + ((int)Hero->MoveDown - (int)Hero->MoveUp) * Acceleration);
    Hero->Move();

    /// BULLETS

    if (Hero->FireOn && Hero->Can_Shoot(Cur_Loop_Iteration) && !GameOver) {
        if (SoundsOn) {
            Mix_PlayChannel(0, Shoot_Sounds[rand() % NUM_SHOOT_SOUNDS], 0);
        }
        Bullets.push_back(Hero->Shoot(Cur_Loop_Iteration, Surf_Bullet, 4 * GAME_SPEED));
    }
    vector <CBullet*> tmp_Bullets(0);
    for (int i = 0; i < (int)Bullets.size(); i++) {
        Bullets[i]->Move();
        for (int j = 0; j < (int)Asteroids.size(); j++) {
            if (!(Asteroids[j]->Need_to_Destroy()) && Intersection(*Bullets[i], *Asteroids[j])) {
                Asteroids[j]->Dec_Health(Bullets[i]->Get_Damage());
                Bullets[i]->Dec_Health(1);
                if (!GameOver) {
                    Score += 100;
                }
                break;
            }
        }
        if (Bullets[i]->Need_to_Destroy()) {
            delete Bullets[i];
        } else {
            tmp_Bullets.push_back(Bullets[i]);
        }
    }
    Bullets = tmp_Bullets;
    tmp_Bullets.clear();

    /// ASTEROIDS

    if (Cur_Loop_Iteration % (int)std::max((ITER_BETWEEN_GEN_ASTEROIDS - Cur_Iteration / 500), 1) == 0) {
        int id = rand() % ASTEROID_TYPES;
        Asteroids.push_back(new CAsteroid(WIDTH_DISPLAY, HEIGHT_DISPLAY, 300 * (GAME_SPEED + Add_Speed) / ITER_PER_SEC,
            50 * (GAME_SPEED + Add_Speed) / ITER_PER_SEC, 0.8, ASTEROIDS_DAMAGE[id], ASTEROIDS_HEALTH[id], ASTEROIDS_COST[id], Surf_Asteroids[id]));
    }
    vector <CAsteroid*> tmp_Asteroids(0);
    for (int i = 0; i < (int)Asteroids.size(); i++) {
        Asteroids[i]->Move();
        if (!GameOver && Intersection(*Hero, *Asteroids[i])) {
            Slight_Health += min(Asteroids[i]->Get_Damage(), Hero->Get_Health());
            Hero->Dec_Health(Asteroids[i]->Get_Damage());
            Asteroids[i]->Make_Dead();
        }
        if (Asteroids[i]->Need_to_Destroy()) {
            if (Asteroids[i]->Get_Health() == 0 && !GameOver) {
                Score += Asteroids[i]->Get_Cost();
            }
            delete Asteroids[i];
        } else {
            tmp_Asteroids.push_back(Asteroids[i]);
        }
    }
    Asteroids = tmp_Asteroids;
    tmp_Asteroids.clear();

    Add_Speed += GAME_SPEED / (100 * ITER_PER_SEC);
    Add_Speed = std::min(Add_Speed, 15.0);
    Slight_Health = max(0, Slight_Health - 1);
    if (Hero->Get_Health() == 0) {
        if (!GameOver) {
            Highscores.Add_Score((char *)"123\0", Score);
        }
        GameOver = true;
    }
}

bool Intersection(CObject First, CObject Second)
{
    int dx = abs(First.Get_X() + First.Get_W() / 2 - Second.Get_X() - Second.Get_W() / 2);
    int dy = abs(First.Get_Y() + First.Get_H() / 2 - Second.Get_Y() - Second.Get_H() / 2);
    double alpha = fabs(atan2(dy, dx));
    alpha = (alpha > M_PI / 2 ? M_PI - alpha : alpha);
    double len = ((First.Get_W() + Second.Get_W()) * (M_PI / 2 - alpha) + (First.Get_H() + Second.Get_H()) * (alpha)) / (1.1 * M_PI);
    return (len > sqrt(dx * dx + dy * dy));
}
