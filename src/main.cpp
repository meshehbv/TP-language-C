#include <Arduino.h>
#include "nfc.h"
#include "led.h"
#include "clavier.h"
#include "lcd.h"
#include "rtc.h"

void setup() {
    Serial.begin(9600);
    led_init();
    nfc_init();
    lcd_init();
    
    // Padded with spaces to ensure previous text is fully overwritten
    lcd_print(0, "Starting up...  ");
    lcd_print(1, "System Ready    ");
    delay(1500); 
    
    lcd_print(0, "Enter admin tag ");
    lcd_print(1, "Waiting...      ");
    while (!tag_present()) {
        delay(50); // Small delay to prevent I2C bus lockup
    }
    
    // The loop breaks when a tag is found. Read and register it.
    struct Tag current_tag = tag_read();
    register_admin_tag(current_tag);
    
    lcd_print(0, "Admin Saved!    ");
    lcd_print(1, "                ");
    delay(2000);
}

void loop() {
    if (tag_present()) {
        struct Tag current_tag = tag_read();
        if (is_tag_known(current_tag)) {
            led_set_color(ColorGreen);
        }
        Serial.print("Tag UID: ");
        for (int i = 0; i < sizeof(current_tag.uid); i++) {
            Serial.print(current_tag.uid[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }


    /*Key currentKey = clavier(); // Read the button from A0
    const char* keyText = keyToString(currentKey);
    
    lcd_print(1, keyText); // Print the button name on the bottom row
    
    delay(100); // Small delay to prevent rapid flickering*/
}