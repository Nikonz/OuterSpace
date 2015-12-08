#ifndef _CHIGHSCORES_H_
#define _CHIGHSCORES_H_

#include <vector>
//#include <algorithm>
#include <unistd.h>
#include <fcntl.h>

using std::vector;
using std::swap;

class CScore
{
    private:
        char* Name;
        int Score;
    public:
        CScore(char* name = NULL, int score = -1);
        virtual ~CScore();

        char* Get_Name();
        int Get_Score();
};

class CHighscores
{
    private:
        vector <CScore> Scores;
        int Max_Scores;
        int File;
    public:
        CHighscores(int max_scores = 5);
        virtual ~CHighscores();
        bool Append_File(char *name);
        void Add_Score(char *name, int score);
        void Load_from_File();
        void Load_to_File();
        void Close_File();
        int Get_Size();
        CScore Get_Score(int ind);
};

#endif // _CHIGHSCORES_H_
