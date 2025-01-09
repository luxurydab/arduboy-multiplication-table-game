#ifndef SCENE_H
#define SCENE_H

#include <Arduboy2.h>
#include "state.h"
#include "blinker.h"
#include "quiz.h"

class Scene { 
public:   
    Arduboy2 arduboy;
    BeepPin1 beep;
    State state;
    Quiz quiz; 
    Blinker blinker;
    String currentScene; 
    String lastScene;
    bool answerInProgress = false;
    bool wrongAnswerSceneInProgress = false;
    bool correctAnswerSceneInProgress = false;      
    Scene(
        Arduboy2 arduboy,
        BeepPin1 beep,
        State state,
        Quiz quiz,
        Blinker blinker
    );
    ~Scene();
    void init();
    void update();
    void loadingScene();
    void developedByScene();
    void startMenuScene();
    void questionScene();
    void renderStats();
    void renderAnswer();
    void renderQuestion();
    void correctAnswerScene();
    void wrongAnswerScene();
    void gameOverScene();
    void handleKeyboard();
    void handleLeftButton();
    void handleRightButton();
    void handleUpButton();
    void handleDownButton();
    void handleAButton();
    void handleBButton();
    void renderKeyboard();
    int countDigits(int num);
    bool isAnyButtonPressed();
};

#endif // SCENE_H