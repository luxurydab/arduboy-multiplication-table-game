#include <Arduino.h>
#include "scene.h"
#include "sprite.h"
#include "keyboard.h"

Scene::Scene(
    Arduboy2 arduboy,
    BeepPin1 beep,
    State state,
    Quiz quiz,
    Blinker blinker
){
    arduboy = arduboy;
    beep = beep;
    state = state;
    quiz = quiz;
    blinker = blinker;
};

Scene::~Scene(){};

void Scene::init()
{
    this->arduboy.begin();
    this->beep.begin(); 
    this->currentScene = "developedBy";
};

void Scene::update()
{
    this->arduboy.pollButtons();
    this->beep.timer(); 
    this->blinker.loop();

    if(this->currentScene != this->lastScene){   
        this->lastScene = this->currentScene;     
        this->arduboy.clear();
    }

    if (this->currentScene == "developedBy"){
        this->developedByScene();
        return;
    }
    if (this->currentScene == "loading"){
        this->loadingScene();
        return;
    }
    if (this->currentScene == "startMenu"){
        this->startMenuScene();
        return;
    }
    if (this->currentScene == "question"){        
        this->questionScene();
        return;
    }
    if (this->currentScene == "correctAnswer"){
        this->correctAnswerScene();
        return;
    }
    if (this->currentScene == "wrongAnswer"){
        this->wrongAnswerScene();    
        return;
    }
    if (this->currentScene == "gameOver"){
        this->gameOverScene();
        return;
    }
};

void Scene::developedByScene()
{
    this->currentScene = "developedBy";
    this->arduboy.setCursor(0, 5); 
    this->arduboy.print("Developed by");
    this->arduboy.setCursor(0, 15); 
    this->arduboy.print("Anton Lohvynenko");  
    this->arduboy.setCursor(0, 40); 
    this->arduboy.print("lohvynenko.com");  
    this->arduboy.display();
    delay(2500);
    this->currentScene = "loading";
}

void Scene::loadingScene()
{
    this->currentScene = "loading";
    this->arduboy.clear(); 
    for (int i = -32; i < 0; i++)
    {    
        Sprites::drawOverwrite(20, i, GAME_LOGO, 0);
        this->arduboy.display(); 
        delay(30);
    }
    Sprites::drawOverwrite(20, 0, GAME_LOGO, 0); 
    this->arduboy.display();
    this->currentScene = "startMenu";
}

void Scene::startMenuScene()
{
    this->currentScene = "startMenu";
    this->blinker.setBlinkInterval(DEFAULT_BLINK_INTERVAL);
    this->arduboy.clear();    
    Sprites::drawOverwrite(20, 0, GAME_LOGO, 0); 
    this->arduboy.setTextSize(1);
    this->arduboy.setCursor(4, 50); 
    if(this->blinker.isVisible()){
      this->arduboy.print(F("\x10 Press any button \x11"));  
    }
    this->arduboy.display();
    if(this->isAnyButtonPressed()){
      this->quiz.begin();
      this->currentScene = "question";
    }
}

void Scene::questionScene()
{
    this->currentScene = "question";   
    this->blinker.setBlinkInterval(10); 
    if(this->answerInProgress == false){
        this->answerInProgress = true;
        this->quiz.generateQuestion();
    }  
    this->renderStats();
    this->renderQuestion();        
    this->handleKeyboard();    
    this->renderKeyboard();
}

void Scene::renderStats()
{
    this->arduboy.setCursor(2, 0);
    this->arduboy.setTextSize(1);
    this->arduboy.print(F("\x03"));  
    this->arduboy.print(" ");
    this->arduboy.print(this->state.getLives());
    this->arduboy.print(" ");
    this->arduboy.print("Score: ");
    this->arduboy.print(this->state.getScore());
    this->arduboy.display();
}

void Scene::renderAnswer()
{
    this->arduboy.setTextSize(2);
    this->arduboy.setCursor(1, 18); 
    this->arduboy.print(this->quiz.getA());
    this->arduboy.print(" x ");
    this->arduboy.print(this->quiz.getB());
    this->arduboy.print(" = ");
    this->arduboy.print(this->quiz.getAnswer());
    this->arduboy.display();
}

void Scene::renderQuestion()
{  
    this->arduboy.setTextSize(2);
    this->arduboy.setCursor(1, 18); 
    this->arduboy.print(this->quiz.getA());
    this->arduboy.print(" x ");
    this->arduboy.print(this->quiz.getB());
    this->arduboy.print(" = ");
    if(this->quiz.isEmptyAnswer()){
        if (this->blinker.isVisible()){
          this->arduboy.print("?"); 
        }else{
          this->arduboy.print(" ");
        }
    }else{
        this->arduboy.print(this->quiz.getAnswer());
    }
    this->arduboy.display();
}

void Scene::correctAnswerScene()
{
    this->currentScene = "correctAnswer"; 
    this->arduboy.digitalWriteRGB(GREEN_LED, RGB_ON);
    this->renderStats();
    this->renderAnswer();  
    Sprites::drawOverwrite(15, 34, SMILE_SPRITE, 0); 
    if(this->correctAnswerSceneInProgress == false){
        this->beep.tone(this->beep.freq(900), 15);
        this->correctAnswerSceneInProgress = true;
        this->state.increaseScore();
    }
    this->arduboy.display();  
    if(this->isAnyButtonPressed()){
        this->correctAnswerSceneInProgress = false;
        this->arduboy.digitalWriteRGB(GREEN_LED, RGB_OFF);
        this->arduboy.clear();
        this->currentScene = "question";
    }
}

void Scene::wrongAnswerScene()
{
    this->currentScene = "wrongAnswer";
    this->arduboy.digitalWriteRGB(RED_LED, RGB_ON);
    this->renderStats();
    this->renderAnswer();
    this->arduboy.drawLine(88, 27, 124, 19);
    this->arduboy.drawLine(88, 28, 124, 20); 
    Sprites::drawOverwrite(15, 34, SAD_SMILE_SPRITE, 0);
    this->arduboy.setTextSize(2);
    this->arduboy.setCursor(96, 42); 
    this->arduboy.print(this->quiz.getCorrectAnswer());
    if(this->wrongAnswerSceneInProgress == false){  
        this->beep.tone(this->beep.freq(150), 15);      
        this->wrongAnswerSceneInProgress = true;
        this->state.decreaseLives();
    }
    if(this->state.getLives() <= 0){
        this->arduboy.digitalWriteRGB(RED_LED, RGB_OFF);
        this->wrongAnswerSceneInProgress = false;
        this->currentScene = "gameOver";
        this->arduboy.clear();
        return;   
    }  
    this->arduboy.display();
    if(this->isAnyButtonPressed()){
        this->arduboy.digitalWriteRGB(RED_LED, RGB_OFF);
        this->wrongAnswerSceneInProgress = false;
        this->arduboy.clear();
        this->currentScene = "question";
    }
}

void Scene::gameOverScene()
{
    this->currentScene = "gameOver";
    this->arduboy.clear();
    this->arduboy.setTextSize(2);  
    this->arduboy.setCursor(40, 5); 
    this->arduboy.print("GAME");
    this->arduboy.setCursor(40, 25); 
    this->arduboy.print("OVER");
    this->arduboy.setCursor(20, 55);
    this->arduboy.setTextSize(1);
    this->arduboy.print("Your Score: ");
    this->arduboy.print(this->state.getScore());
    this->arduboy.display();

    if(this->isAnyButtonPressed()){
      this->arduboy.clear();
      this->state.reset();
      this->currentScene = "startMenu";
    }
}

void Scene::handleKeyboard()
{
  if (this->arduboy.everyXFrames(4)) {
    if (this->arduboy.justPressed(LEFT_BUTTON)) {
      this->handleLeftButton();
      return;
    }

    if (this->arduboy.justPressed(RIGHT_BUTTON)) {
      this->handleRightButton();
      return;
    }

    if (this->arduboy.justPressed(UP_BUTTON)) {
      this->handleUpButton();
      return;
    }

    if (this->arduboy.justPressed(DOWN_BUTTON)) {
      this->handleDownButton();
      return;
    }

    if (this->arduboy.justPressed(A_BUTTON)) { 
      this->handleAButton();      
      return;
    }

    if (this->arduboy.justPressed(B_BUTTON)) {
      this->handleBButton();
      return;
    }   
  }    
}

void Scene::handleLeftButton()
{
    if(currentKey.index > 0){
      currentKey = keyboard[currentKeyboardRow][currentKey.index-1];
    }else if(currentKeyboardRow == 0 && currentKey.index == 0){
      currentKey = keyboard[currentKeyboardRow][KEYBOARD_FIRST_ROW_ELEMENTS-1];
    }else if(currentKeyboardRow == 1 && currentKey.index == 0){
      currentKey = keyboard[currentKeyboardRow][KEYBOARD_SECOND_ROW_ELEMENTS-1];
    }   
}

void Scene::handleRightButton()
{
    if(currentKeyboardRow == 0){
      if(currentKey.index < KEYBOARD_FIRST_ROW_ELEMENTS-1){      
        currentKey = keyboard[currentKeyboardRow][currentKey.index+1];
      }else if(currentKey.index == KEYBOARD_FIRST_ROW_ELEMENTS-1){
        currentKey = keyboard[currentKeyboardRow][0];
      }
    }
    if(currentKeyboardRow == 1){
      if(currentKey.index < KEYBOARD_SECOND_ROW_ELEMENTS-1){      
        currentKey = keyboard[currentKeyboardRow][currentKey.index+1];
      }else if(currentKey.index == KEYBOARD_SECOND_ROW_ELEMENTS-1){
        currentKey = keyboard[currentKeyboardRow][0];
      }
    }      
}

void Scene::handleUpButton()
{
    if(currentKeyboardRow == 1){
      currentKeyboardRow = 0;
      currentKey = keyboard[currentKeyboardRow][0];
    } 
}

void Scene::handleDownButton()
{
    if(currentKeyboardRow == 0){
        currentKeyboardRow = 1;
        currentKey = keyboard[currentKeyboardRow][1];
    } 
}

void Scene::handleAButton()
{
    int digits = this->countDigits(this->quiz.getAnswer());      
    String concatenated = "";   
    if(currentKey.value == 68){ //DEL button
      if(digits <= 1){
        this->quiz.clearAnswer();    
      }    
      if(digits >= 2){
        concatenated = concatenated[0];     
        this->quiz.setAnswer(concatenated.toInt());
      }
      this->arduboy.clear();
    }else if(currentKey.value == 69){ //ENTER button
      if(this->quiz.isEmptyAnswer()){
        return;
      }
      this->answerInProgress = false;
      if(this->quiz.isCorrectAnswer()){             
        this->currentScene = "correctAnswer";      
      }else{
        this->currentScene = "wrongAnswer";
      }
    }else{
      if(this->quiz.isEmptyAnswer()){
        this->quiz.setAnswer(currentKey.value);
        return;
      }      
      concatenated = String(this->quiz.getAnswer()) + String(currentKey.value);       
      if(digits >= 2){
        concatenated = concatenated[0] + String(currentKey.value);     
      }
      this->quiz.setAnswer(concatenated.toInt());
    }
}

void Scene::handleBButton()
{
    this->quiz.clearAnswer();
    this->arduboy.clear();
}

void Scene::renderKeyboard()
{  
  this->arduboy.setTextSize(1);
  this->arduboy.setCursor(4, 46);
  for (keyboardKey key : keyboard[0]) {    
    if(key.value == currentKey.value){
      if (this->blinker.isVisible()){
        this->arduboy.print(key.title); 
      }else{
        String placeholder = "";
        for (char s: key.title) {
          placeholder += " ";
        }
        this->arduboy.print(placeholder);
      }
    }else{
       this->arduboy.print(key.title); 
    }
    this->arduboy.print(" ");
  }  
  this->arduboy.setCursor(40, 56);  
  for (keyboardKey key : keyboard[1]) {
    if(key.value == currentKey.value){
      if (this->blinker.isVisible()){
        this->arduboy.print(key.title); 
      }else{
        String placeholder = "";
        for (char s: key.title) {
          placeholder += " ";
        }
        this->arduboy.print(placeholder);
      }
    }else{
      this->arduboy.print(key.title); 
    }
    this->arduboy.print(" ");
  }    
  this->arduboy.display();
}

int Scene::countDigits(int num) {
    int count = 0;
    num = abs(num);
    do {
        count++;
        num /= 10;
    } while (num != 0);

    return count;
}

bool Scene::isAnyButtonPressed()
{
  if( this->arduboy.justPressed(A_BUTTON) == true
   || this->arduboy.justPressed(B_BUTTON) == true
   || this->arduboy.justPressed(UP_BUTTON) == true
   || this->arduboy.justPressed(DOWN_BUTTON) == true
   || this->arduboy.justPressed(LEFT_BUTTON) == true
   || this->arduboy.justPressed(RIGHT_BUTTON) == true
  ) {
    return true;
  }else{
    return false;
  }
}