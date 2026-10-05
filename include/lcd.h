#pragma once
#include "arduino.h"
/*
Initialise l'afficheur LCD
Cette fonction doit être appelée dans la fonction setup
*/
void lcd_init();
/*
Affiche le texte donné en paramètre sur la ligne indiqué.
*/
void lcd_print(unsigned char row, const char * text)