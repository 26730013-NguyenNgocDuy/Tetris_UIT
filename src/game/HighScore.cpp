#include "HighScore.h"

#include <fstream>

HighScore::HighScore(const std::string &file)
{
    fileName = file;
    best = 0;

    std::ifstream in(fileName.c_str());
    if (!(in >> best) || best < 0)
        best = 0;   // chưa có file hoặc file hỏng thì coi như chưa có kỷ lục
}

void HighScore::submit(int score)
{
    if (score <= best)
        return;

    best = score;
    std::ofstream out(fileName.c_str());
    if (out)
        out << best;
}
