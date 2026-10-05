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
void lcd_print(unsigned char row, const char * text);

struct menu_admin
{
    int current_index = 0; // Tracks the current menu option (0, 1, or 2)
    void scroll_menu();    //[cite: 5]
    void selected_option();//[cite: 5]
};
