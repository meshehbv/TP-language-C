#pragma once
#include <Arduino.h>

enum class Key {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SELECT
};

Key clavier();
const char* keyToString(Key k);

