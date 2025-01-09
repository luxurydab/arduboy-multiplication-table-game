#include "quiz.h"
#include "randomizer.h"

Randomizer randomizer;

Quiz::Quiz()
{
    this->begin();
}

Quiz::~Quiz()
{
}

void Quiz::begin()
{
    randomizer.initRandom();
}

bool Quiz::isCorrectAnswer()
{
    return (this->answer == this->correctAnswer);
}

void Quiz::generateQuestion()
{
    this->a = randomizer.rangedRand(2, 9);
    this->b = randomizer.rangedRand(2, 9);
    this->correctAnswer = this->a * this->b;
    this->clearAnswer();   
}

int Quiz::getA()
{
    return this->a;
}

int Quiz::getB()
{
    return this->b;
}

int Quiz::getAnswer()
{
    return this->answer;
}

int Quiz::getCorrectAnswer()
{
    return this->correctAnswer;
}

void Quiz::clearAnswer()
{
    this->answer = -1;
}

void Quiz::setAnswer(int answer)
{
    this->answer = answer;
}

bool Quiz::isEmptyAnswer()
{
    return (this->answer == -1);
}