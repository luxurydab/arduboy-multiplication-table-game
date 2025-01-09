#include "state.h"

State::State(){};
State::~State(){};

void State::reset()
{
    this->lives = 5;
    this->score = 0;
};

void State::setLives(unsigned short lives)
{
    this->lives = lives;
};

void State::decreaseLives()
{
    this->lives--;
};

void State::setScore(unsigned int score)
{
    this->score = score;
};

void State::increaseScore()
{
    this->score++;
};

unsigned short State::getLives()
{
    return this->lives;
};

unsigned int State::getScore()
{
    return this->score;
};    