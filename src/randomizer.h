#ifndef RANDOMIZER_H
#define RANDOMIZER_H

class Randomizer
{
private:
public:
    Randomizer();
    ~Randomizer();
    void initRandom();
    int rangedRand(const int & min, const int & max); 
};

#endif // RANDOMIZER_H