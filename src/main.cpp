#include <Arduino.h>
#include "nfc.h"
#include "led.h"

void setup() {
    Serial.begin(115200);
    led_init();
    nfc_init();
}

void loop() {
    if (tag_present()) {
        struct Tag current_tag = tag_read();
        
        // Allumer la LED en vert si le badge est connu (géré par nfc.cpp), sinon en rouge
        if (is_tag_known(current_tag)) {
            led_set_color(ColorGreen);
        } else {
            led_set_color(ColorRed);
        }
        
        delay(2000); 
    } else {
        led_set_color((LedColor)(ColorBlue | ColorGreen));
        delay(500);
        led_set_color(ColorOff);
        delay(500);
    }
}