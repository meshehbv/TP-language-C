#include "lcd.h"
#include <stdio.h>
#include <LiquidCrystal.h>
// Constantes des dimensions de l'écran
#define COLUMN_COUNT 16
#define ROWN_COUNT 2
LiquidCrystal liquidcrystal(8, 9, 4, 5, 6, 7);
static char buffer[COLUMN_COUNT +1];



void lcd_init()
{// set up the LCD's number of columns and rows:
liquidcrystal.begin(COLUMN_COUNT, ROWN_COUNT);
liquidcrystal.clear();
}

void lcd_print_internal(const char * text)
{
memset(buffer, ' ', sizeof(buffer));
size_t length = strlen(text);
if(length > COLUMN_COUNT)
{
length = COLUMN_COUNT;
}
strncpy(buffer, text, length);
liquidcrystal.print(buffer);
}

void lcd_print(unsigned char row, const char * text)
{
liquidcrystal.setCursor(0,row);
lcd_print_internal(text);
}

// Array of options padded to exactly 16 characters including the "<-"
const char* admin_options[3] = {
    "Badge user    <-", 
    "Badge admin   <-", 
    "Heure horloge <-"  
};

void menu_admin::scroll_menu() {
    // Increment the index and loop back to 0 if it exceeds the 3 options
    current_index++;
    if (current_index > 2) {
        current_index = 0;
    }
    
    // Row 0 is always "Menu Admin"
    lcd_print(0, "Menu Admin      ");
    
    // Row 1 displays the currently selected option with the arrow
    lcd_print(1, admin_options[current_index]);
}

void menu_admin::selected_option() {
    // Optional display feedback when the user presses "SELECT"
    lcd_print(0, "Option choisie: ");
    lcd_print(1, admin_options[current_index]);
}