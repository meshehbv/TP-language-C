#pragma once
#include "arduino.h"
#include <RTClib.h>
/*
Initialise l’horloge
Cette fonction doit être appelée dans la fonction setup
*/
void rtc_init();
/*
Lecture de l’horloge
*/
DateTime rtc_get_current_time();
/*
Mise à jour de l’heure de l’horloge
*/
void rtc_set_current_time(DateTime datetime);