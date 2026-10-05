#include "nfc.h"
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

#define MAX_KNOWN_TAGS 20
#define MAX_ADMIN_TAGS 5

struct Tag known_tags[MAX_KNOWN_TAGS];
struct Tag admin_tag[MAX_ADMIN_TAGS];

static int num_known_tags = 0;
static int num_admin_tags = 0;


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

bool is_tag_admin(struct Tag tag_to_check) {
    for (int i = 0; i < num_admin_tags; i++) {
        if (tag_are_equals(tag_to_check, admin_tag[i])) {
            return true;
        }
    }
    return false;
}

bool register_user_tag(struct Tag new_tag) {
    if (num_known_tags >= MAX_KNOWN_TAGS) return false; // Array full
    if (is_tag_known(new_tag)) return false;            // Already registered
    
    known_tags[num_known_tags] = new_tag;
    num_known_tags++;
    return true;
}

// Registers a struct Tag as an admin
bool register_admin_tag(struct Tag new_tag) {
    if (num_admin_tags >= MAX_ADMIN_TAGS) return false; // Array full
    if (is_tag_admin(new_tag)) return false;            // Already admin
    
    admin_tag[num_admin_tags++] = new_tag;
    known_tags[num_known_tags++] = new_tag; // Also register as known
    return true;
}

// Reads a tag currently on the scanner and registers it as a user
bool register_presented_tag() {
    if (tag_present()) {
        struct Tag new_tag = tag_read();
        return register_user_tag(new_tag);
    }
    return false;
}

bool replace_admin_tag(struct Tag new_admin) {
    // "Delete" the previous admin by resetting the counter to 0
    num_admin_tags = 0;
    
    // Add the new tag as the single active admin
    admin_tag[0] = new_admin;
    num_admin_tags = 1;

    // If the tag is already a user, it simply gains admin rights.
    // If it is NOT a user yet, add it to the known_tags array so it can trigger "Ouverture".
    if (!is_tag_known(new_admin)) {
        if (num_known_tags < MAX_KNOWN_TAGS) {
            known_tags[num_known_tags] = new_admin;
            num_known_tags++;
        } else {
            return false; // User array is full
        }
    }
    return true;
}