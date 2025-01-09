#include <Arduino.h>
#include "randomizer.h"

Randomizer::Randomizer()
{
  this->initRandom();
}

Randomizer::~Randomizer()
{
}

void Randomizer::initRandom()
{
  randomSeed(analogRead(A0) + millis());
}

int Randomizer::rangedRand(const int & min, const int & max)
{
  return random(min, max);
}