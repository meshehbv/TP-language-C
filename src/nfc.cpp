#include "nfc.h"
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

// Tableau de badges préenregistrés caché dans nfc.cpp
static const struct Tag known_tags[] = {
    {{0xC7, 0x4D, 0x4F, 0x03}}, 
    {{0x1A, 0x3A, 0x1C, 0x18}}
};
static const int num_known_tags = sizeof(known_tags) / sizeof(known_tags[0]);


bool nfc_init() {
    nfc.begin();
    return true;
}

bool tag_present() {
    return nfc.tagPresent(100);
}

struct Tag tag_read() {
    Tag tag;
    NfcTag nfcTag = nfc.read();
    nfcTag.getUid(tag.uid, sizeof(tag.uid)/sizeof(byte));
    return tag;
}

bool tag_are_equals(struct Tag tag1, struct Tag tag2) {
    return memcmp(tag1.uid, tag2.uid, sizeof(tag1.uid)) == 0;
}

// Nouvelle fonction qui gère la vérification en interne
bool is_tag_known(struct Tag tag_to_check) {
    for (int i = 0; i < num_known_tags; i++) {
        if (tag_are_equals(tag_to_check, known_tags[i])) {
            return true;
        }
    }
    return false;
}