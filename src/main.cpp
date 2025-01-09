#include <Arduboy2.h>
#include <Arduboy2Beep.h>
#include "sprite.h"
#include "state.h"
#include "blinker.h"
#include "quiz.h"
#include "scene.h"

Arduboy2 arduboy;
Blinker blinker;
BeepPin1 beep;
State state;
Quiz quiz;
Scene scene(
  arduboy,
  beep,
  state,
  quiz,
  blinker
);

void setup() { 
  scene.init();  
}

void loop() {        
  scene.update();  
}