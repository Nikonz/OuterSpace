#include "../headers/CHighscores.h"

/// ====== CScore ======

CScore::CScore(char* name, int score)
{
    Name = name;
    Score = score;
}

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

CScore::~CScore() {};

char* CScore::Get_Name()
{
    return Name;
}

int CScore::Get_Score()
{
    return Score;
}

/// ==== CHighscores ====

CHighscores::CHighscores(int max_scores)
{
    File = -1;
    Max_Scores = max_scores;
    Scores.clear();
}

CHighscores::~CHighscores()
{
    for (int i = 0; i < (int)Scores.size(); i++) {
        delete [] Scores[i].Get_Name();
    }
};

bool CHighscores::Append_File(char* name)
{
    return ((File = open(name, O_CREAT | O_RDWR)) != -1);
}

void CHighscores::Load_from_File()
{
    int n = 0;
    read(File, &n, sizeof(n));
    for (int i = 0; i < n; i++) {
        char* name = new char[20];
        memset(name, 0, 10);
        int sz = 0, score = 0;
        read(File, &sz, sizeof(sz));
        read(File, name, sz);
        read(File, &score, sizeof(score));
        Scores.push_back(CScore(name, score));
    }
    if ((int)Scores.size() > Max_Scores) {
        Scores.resize(Max_Scores);
    }
}

void CHighscores::Load_to_File()
{
    lseek(File, SEEK_SET, 0);
    int n = Scores.size();
    write(File, &n, sizeof(n));
    for (int i = 0; i < (int)Scores.size(); i++) {
        int sz = strlen(Scores[i].Get_Name());
        write(File, &sz, sizeof(sz));
        write(File, Scores[i].Get_Name(), sz);
        int score = Scores[i].Get_Score();
        write(File, &score, sizeof(score));
    }
}

void CHighscores::Close_File()
{
    close(File);
}

void CHighscores::Add_Score(char* name, int score)
{
    char* tmp = new char[20];
    sprintf(tmp, "%s", name);
    Scores.push_back(CScore(tmp, score));
    for (int i = (int)Scores.size() - 1; i > 0; i--) {
        if (Scores[i - 1].Get_Score() < Scores[i].Get_Score()) {
            swap(Scores[i - 1], Scores[i]);
        }
    }
    if ((int)Scores.size() > Max_Scores) {
        for (int i = Max_Scores; i < (int)Scores.size(); i++) {
            delete Scores[i].Get_Name();
        }
        Scores.resize(Max_Scores);
    }
}

int CHighscores::Get_Size()
{
    return Scores.size();
}

CScore CHighscores::Get_Score(int ind)
{
    return Scores[ind];
}
