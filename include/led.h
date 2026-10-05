#pragma once
#include <Arduino.h>

/*
Énumération des couleurs que la LED peut prendre
*/
enum LedColor
{
    ColorOff = 0,
    ColorBlue = 1,
    ColorGreen = 2,
    ColorRed = 4,
};

/*
Initialisation de la LED
Cette fonction doit être appelée dans la fonction setup
*/
void led_init();

/*
Affichage de la couleur passée en paramètre
*/
void led_set_color(LedColor color);