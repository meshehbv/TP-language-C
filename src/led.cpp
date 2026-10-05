#include "led.h"

// Broches de la LED
#define PIN_BLUE 17
#define PIN_GREEN 16
#define PIN_RED 15

void led_init() {
    pinMode(PIN_BLUE, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_RED, OUTPUT);
    led_set_color(ColorOff);
}

void led_set_color(LedColor color) {
    // Les valeurs de l'enum permettent un masquage binaire pour activer les bonnes couleurs
    digitalWrite(PIN_BLUE, (color & ColorBlue) ? HIGH : LOW);
    digitalWrite(PIN_GREEN, (color & ColorGreen) ? HIGH : LOW);
    digitalWrite(PIN_RED, (color & ColorRed) ? HIGH : LOW);
}