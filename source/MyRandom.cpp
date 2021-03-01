#include "../headers/MyRandom.h"

MyRandom::MyRandom()
    :  m_random_engine(std::random_device{}()),
    m_dist{1, 10} { }

MyRandom::MyRandom(int min, int max)
  :  m_random_engine(std::random_device{}()),
  m_dist{min, max} { }

int MyRandom::get()
{
    return m_dist(m_random_engine);
}

int MyRandom::get(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_random_engine);
}
