#ifndef QUIZ_H
#define QUIZ_H

class Quiz
{
    private:
        unsigned short a, b = 0;
        int correctAnswer;
        int answer;
    public:
        Quiz();
        ~Quiz();
        void begin();
        bool isCorrectAnswer();
        void generateQuestion();
        int getA();
        int getB();    
        int getAnswer(); 
        int getCorrectAnswer();
        void clearAnswer();
        void setAnswer(int answer);
        bool isEmptyAnswer();
};

#endif // QUIZ_H