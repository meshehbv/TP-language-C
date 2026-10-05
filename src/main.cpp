#include <Arduino.h>
#include "nfc.h"
#include "led.h"
#include "clavier.h"
#include "lcd.h"
#include "rtc.h"

bool in_admin_menu = false;
menu_admin my_admin_menu;

// Helper function to easily reset the display to the main menu
void draw_main_menu() {
    lcd_print(0, "Main Menu       ");
    lcd_print(1, "Scan badge...   ");
}

void setup() {
    Serial.begin(9600);
    led_init();
    nfc_init();
    lcd_init();
    
    lcd_print(0, "Starting up...  ");
    lcd_print(1, "System Ready    ");
    delay(1500); 
    
    lcd_print(0, "Enter admin tag ");
    lcd_print(1, "Waiting...      ");
    
    while (!tag_present()) {
        delay(50); // Small delay to prevent I2C bus lockup
    }
    
    // Read and register the first admin
    struct Tag current_tag = tag_read();
    register_admin_tag(current_tag);
    
    lcd_print(0, "Admin Saved!    ");
    lcd_print(1, "                ");
    delay(2000);
    
    // Transition to the main menu after setup
    draw_main_menu();
}

void loop() {
    // STATE 1: STANDARD MODE (Main Menu)
    if (!in_admin_menu) {
        if (tag_present()) {
            struct Tag current_tag = tag_read();
            
            // 1. If Admin: Transition to admin menu
            if (is_tag_admin(current_tag)) {
                in_admin_menu = true;
                led_set_color(ColorBlue);    
                my_admin_menu.scroll_menu(); // Display first admin option
                delay(1000);                 
                return;                      
            }
            
            // 2. If Known User: Grant access
            if (is_tag_known(current_tag)) {
                lcd_print(0, "Ouverture       ");
                lcd_print(1, "                ");
                led_set_color(ColorGreen);
            } 
            // 3. If Unknown: Deny access
            else {
                lcd_print(0, "Acces Refuse    ");
                lcd_print(1, "                ");
                led_set_color(ColorRed);
            }
            
            delay(5000); 
            // Reset to main menu and turn off LEDs
            draw_main_menu();
            led_set_color(ColorOff);
        } else {
            // Optional: Idle LED blinking while waiting for tags
            led_set_color((LedColor)(ColorBlue | ColorGreen));
            delay(500);
            led_set_color(ColorOff);
            delay(500);
        }
    } 
    // STATE 2: ADMIN MENU MODE (Listening to keypad)
    else {
        Key currentKey = clavier(); 
        
        if (currentKey == Key::UP || currentKey == Key::DOWN) {
            my_admin_menu.scroll_menu();
            delay(250); // Debounce delay
        } 
        else if (currentKey == Key::SELECT) {
            my_admin_menu.selected_option();
            delay(1000); 
            
            // Handle the specific logic based on what option was selected
            if (my_admin_menu.current_index == 0) {
                // Register User Badge
                lcd_print(0, "Scan new user   ");
                lcd_print(1, "Waiting...      ");
                
                while (!tag_present()) { delay(50); } // Block until a tag is scanned
                
                struct Tag new_user = tag_read();
                if (register_user_tag(new_user)) {
                    lcd_print(0, "User Saved!     ");
                } else {
                    lcd_print(0, "Error/Full!     ");
                }
                lcd_print(1, "                ");
                delay(2000);
                my_admin_menu.scroll_menu(); // Redraw the admin menu
                
            } else if (my_admin_menu.current_index == 1) {
                // Replace Admin Badge
                lcd_print(0, "Scan new admin  ");
                lcd_print(1, "Waiting...      ");
                
                while (!tag_present()) { delay(50); } // Block until a tag is scanned
                
                struct Tag new_admin = tag_read();
                
                if (replace_admin_tag(new_admin)) {
                    lcd_print(0, "Admin Replaced! ");
                } else {
                    lcd_print(0, "Error/Full!     ");
                }
                
                lcd_print(1, "                ");
                delay(2000);
                my_admin_menu.scroll_menu(); // Redraw the admin menu
                
            } else if (my_admin_menu.current_index == 2) {
                // Clock logic placeholder
                lcd_print(0, "Not implemented ");
                delay(2000);
                my_admin_menu.scroll_menu();
            }
        }
        else if (currentKey == Key::RIGHT) { 
            // Exit Admin Menu
            in_admin_menu = false;
            led_set_color(ColorOff);
            draw_main_menu(); // Restore main menu text
            delay(500);
        }
    }
}