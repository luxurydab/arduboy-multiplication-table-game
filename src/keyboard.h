#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <Arduino.h>

struct keyboardKey {
  int value;
  int index;
  String title;
};
const int KEYBOARD_ROWS = 2;
const int KEYBOARD_FIRST_ROW_ELEMENTS = 10;
const int KEYBOARD_SECOND_ROW_ELEMENTS = 2;
const keyboardKey keyboard[KEYBOARD_ROWS][10] = {
    {
      {1, 0, "1"},
      {2, 1, "2"},
      {3, 2, "3"},
      {4, 3, "4"},
      {5, 4, "5"},
      {6, 5, "6"},
      {7, 6, "7"},
      {8, 7, "8"},
      {9, 8, "9"},
      {0, 9, "0"}  
    },
    {
      {'D', 0, "\x1B DEL"},
      {'E', 1, "\x10 ENTER"}
    }
};
int currentKeyboardRow = 0;
keyboardKey currentKey = keyboard[currentKeyboardRow][0];   

#endif // KEYBOARD_H