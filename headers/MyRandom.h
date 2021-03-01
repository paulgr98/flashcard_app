#pragma once
#include <random>

class MyRandom
{
private:
    std::mt19937 m_random_engine;
    std::uniform_int_distribution<int> m_dist;

public:
    MyRandom();
    MyRandom(int max, int min);

    int get();
    int get(int min, int max);
};