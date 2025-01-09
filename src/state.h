#ifndef STATE_H
#define STATE_H

class State
{
    private:
        unsigned short lives = 5;
        unsigned int score = 0;
    public:
        State();
        ~State();
        void reset();
        void setLives(unsigned short lives);
        void decreaseLives();
        void setScore(unsigned int score);
        void increaseScore();        
        unsigned short getLives();      
        unsigned int getScore();      
};

#endif // STATE_H