#include "keymap_common.h"
#include <avr/wdt.h>

/* id for user defined functions */
enum function_id {
    PROMICRO_PROGRAM,
};

/*
 * Macropad
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer */
    KEYMAP(
                 FN0,     FN1, FN2, FN3, FN4,   \
                 NLCK,
                          PPLS,PSLS,PAST,PMNS, \
       INS, HOME,PGUP,    P7,  P8,  P9,  DEL,  \
       DEL, END, PGDN,    P4,  P5,  P6,  LEFT, \
       VOLD,UP,  VOLU,    P1,  P2,  P3,  RGHT, \
       LEFT,DOWN,RGHT,    P0,  BSPC,PDOT,ENT),
    /* Keymap 1: Function Keys */
    KEYMAP(
                 FN0,     FN1, FN2, FN3, FN4,   \
                 NLCK,
                          PPLS,PSLS,PAST,PMNS, \
       F1,  F2,  F3,      P7,  P8,  P9,  DEL,  \
       F4,  F5,  F6,      P4,  P5,  P6,  LEFT, \
       F7,  F8,  F9,      P1,  P2,  P3,  RGHT, \
       F10, F11, F12,     P0,  BSPC,PDOT,ENT),
    /* Keymap 2: Extended function keys*/
    KEYMAP(
                 FN25,     FN1, FN2, FN3, FN4,   \
                 FN26,
                          PPLS,PSLS,PAST,PMNS, \
       F13, F14, F15,     P7,  P8,  P9,  DEL,  \
       F16, F17, F18,     P4,  P5,  P6,  LEFT, \
       F19, F20, F21,     P1,  P2,  P3,  RGHT, \
       F22, F23, F24,     P0,  BSPC,PDOT,ENT),
    /* Keymap 3: Shifted function keys */
    KEYMAP(
                 FN25,     FN1, FN2, FN3, FN4,   \
                 FN26,
                          PPLS,PSLS,PAST,PMNS, \
       FN13,FN14,FN15,    P7,  P8,  P9,  DEL,  \
       FN16,FN17,FN18,    P4,  P5,  P6,  LEFT, \
       FN19,FN20,FN21,    P1,  P2,  P3,  RGHT, \
       FN22,FN23,FN24,    P0,  BSPC,PDOT,ENT),   
    /* Keymap 4: Shifted function keys */
    KEYMAP(
                 TRNS,    FN1, FN2, FN3, FN4,   \
                 FN5,
                          PPLS,PSLS,PAST,PMNS, \
       TRNS,TRNS,TRNS,    P7,  P8,  P9,  DEL,  \
       TRNS,TRNS,TRNS,    P4,  P5,  P6,  LEFT, \
       TRNS,TRNS,TRNS,    P1,  P2,  P3,  RGHT, \
       TRNS,TRNS,TRNS,    P0,  BSPC,PDOT,ENT),
};

/*
 * Fn action definition
 */
const action_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_KEY(4, KC_PSCR), //switch to the sneaky layer
    [1] = ACTION_DEFAULT_LAYER_SET(0),  // set default layout
    [2] = ACTION_DEFAULT_LAYER_SET(1),  // set function keys
    [3] = ACTION_DEFAULT_LAYER_SET(2),  // set macros
    [4] = ACTION_DEFAULT_LAYER_SET(3),  // set shifted macros
    [5] = ACTION_FUNCTION(PROMICRO_PROGRAM),
    //Macro record keys
    [10] = ACTION_MODS_KEY(MOD_LSFT, KC_F1), //Combo key that I decided not to use
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_F2), //Another one
    
    //Shifted fuction keys starting from F13
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_F13),
    [14] = ACTION_MODS_KEY(MOD_LSFT, KC_F14),
    [15] = ACTION_MODS_KEY(MOD_LSFT, KC_F15),
    [16] = ACTION_MODS_KEY(MOD_LSFT, KC_F16),
    [17] = ACTION_MODS_KEY(MOD_LSFT, KC_F17),
    [18] = ACTION_MODS_KEY(MOD_LSFT, KC_F18),
    [19] = ACTION_MODS_KEY(MOD_LSFT, KC_F19),
    [20] = ACTION_MODS_KEY(MOD_LSFT, KC_F20),
    [21] = ACTION_MODS_KEY(MOD_LSFT, KC_F21),
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_F22),
    [23] = ACTION_MODS_KEY(MOD_LSFT, KC_F23),
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_F24),

    [25] = ACTION_MODS_KEY(MOD_LCTL, KC_F12),
    [26] = ACTION_MODS_KEY(MOD_LCTL, KC_F13),
  
};

void promicro_bootloader_jmp(bool program) {
    uint16_t *const bootKeyPtr = (uint16_t *)0x0800;

    // Value used by Caterina bootloader use to determine whether to run the
    // sketch or the bootloader programmer.
    uint16_t bootKey = program ? 0x7777 : 0;

    *bootKeyPtr = bootKey;

    // setup watchdog timeout
    wdt_enable(WDTO_60MS);

    while(1) {} // wait for watchdog timer to trigger
}

/*
* user defined action function
*/
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id) {
        case PROMICRO_PROGRAM:
            promicro_bootloader_jmp(true);
            break;
        default:
            break;
    }
}