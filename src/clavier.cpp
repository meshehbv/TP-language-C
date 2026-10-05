#include "clavier.h"
#include <Arduino.h>
#define Button_clavier A0


Key clavier() {
    switch (analogRead(Button_clavier)) {
        case 0 ... 50:
            return Key::RIGHT; 
        case 51 ... 200:
            return Key::UP;
        case 201 ... 350:
            return Key::DOWN;
        case 351 ... 500:
            return Key::LEFT;
        case 501 ... 750:
            return Key::SELECT;
        default:
            return Key::NONE;
    }
    
}

const char* keyToString(Key k) {
  switch (k) {
    case Key::UP:     return "UP      ";
    case Key::DOWN:   return "DOWN    ";
    case Key::LEFT:   return "LEFT    ";
    case Key::RIGHT:  return "RIGHT   ";
    case Key::SELECT: return "SELECT  ";
    case Key::NONE:   return "NONE    ";
    default:          return "        ";
  }
}

