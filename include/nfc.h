#pragma once
#include <Arduino.h>

/*
Définition du type Tag, contenant les informations du badge présenté sur le lecteur NFC.
*/
struct Tag
{
    byte uid[4];
};

/*
Initialisation du lecteur NFC
Cette fonction doit être appelée dans la fonction setup
*/
bool nfc_init();

/*
Permet de vérifier si un badge est présent sur le lecteur NFC.
*/
bool tag_present();

/*
Lis les informations du badge présent sur le lecteur NFC.
S'il n'y a pas de badge, la fonction est bloquante jusqu'à ce qu'un badge soit présenté.
*/
struct Tag tag_read();

bool tag_are_equals(struct Tag tag1, struct Tag tag2);

bool is_tag_known(struct Tag tag_to_check);
