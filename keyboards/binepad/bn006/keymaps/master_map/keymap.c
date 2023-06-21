/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

// enum my_keycodes {

// }

#define _HOME 0
#define _DRAFTS 1
#define _SHAPR3D 2
#define _PIXELSTUDIO 3  

enum combos {
    BOOTKB,
    UPLYR_1,
    UPLYR_2,
    UPLYR_3,
    UPLYR_4,
    DNLYR_4,
    DNLYR_3,
    DNLYR_2,
    DNLYR_1
};

//LIGHTING

// bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//     if (host_keyboard_led_state().caps_lock) {
//         RGB_MATRIX_INDICATOR_SET_COLOR(5, 255, 255, 255); // assuming caps lock is at led #5
//     } else {
//         RGB_MATRIX_INDICATOR_SET_COLOR(5, 0, 0, 0);
//     }
//     return false;
// }

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case _PIXELSTUDIO: 
                rgb_matrix_set_color(i, RGB_MAGENTA);
                break;
            case _SHAPR3D: 
                rgb_matrix_set_color(i, RGB_BLUE);
                break;    
            case _DRAFTS: 
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            default:
                break;
        }
    }
    return false;
}

// COMBOS 

const uint16_t PROGMEM boot_kb [] = {KC_VOLD, KC_VOLU, RSG(KC_TAB), LCMD(KC_TAB), COMBO_END};
const uint16_t PROGMEM up_lyr1 [] = {KC_VOLU, LCMD(KC_TAB), COMBO_END};
const uint16_t PROGMEM up_lyr2 [] = {LCMD(KC_V), LCTL(LCMD(KC_H)), COMBO_END};
const uint16_t PROGMEM up_lyr3 [] = {SCMD(KC_Z), KC_ESC, COMBO_END};
const uint16_t PROGMEM up_lyr4 [] = {KC_Y, KC_3, COMBO_END};
const uint16_t PROGMEM dn_lyr4 [] = {KC_Z, KC_1, COMBO_END};
const uint16_t PROGMEM dn_lyr3 [] = {LCMD(KC_Z), KC_DEL, COMBO_END};
const uint16_t PROGMEM dn_lyr2 [] = {LCMD(KC_C), LCMD(KC_SLSH), COMBO_END};
const uint16_t PROGMEM dn_lyr1 [] = {KC_VOLD, RSG(KC_TAB), COMBO_END};

combo_t key_combos[] = {
  [BOOTKB] = COMBO(boot_kb, QK_BOOT),  // This combo will put the keyboard into DFU mode for flashing
  [UPLYR_1] = COMBO(up_lyr1, TO(_DRAFTS)),
  [UPLYR_2] = COMBO(up_lyr2, TO(_SHAPR3D)),
  [UPLYR_3] = COMBO(up_lyr3, TO(_PIXELSTUDIO)),
  [UPLYR_4] = COMBO(up_lyr4, TO(_HOME)),
  [DNLYR_4] = COMBO(dn_lyr4, TO(_SHAPR3D)),
  [DNLYR_3] = COMBO(dn_lyr3, TO(_DRAFTS)),
  [DNLYR_2] = COMBO(dn_lyr2, TO(_HOME)),
  [DNLYR_1] = COMBO(dn_lyr1, TO(_PIXELSTUDIO))

};
/*
     *
     * ,-----------------------.
     * |   +   |       |   +   |
     * |-------+-------+-------|
     * |   +   |       |   +   |
     * `-----------------------' This enables the DFU through QK BOOT
     *
     */
/*
     *
     * ,-----------------------.
     * |       |       |   +   |
     * |-------+-------+-------|
     * |       |       |   +   |
     * `-----------------------' This will turn on the next highest layer regardless of current layer state
     *
     */

// combo_t key_combos[COMBO_COUNT] = {
//     COMBO(boot_kb, QK_BOOT), // This combo will put the keyboard into DFU mode for flashing
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     *
     * ,-----------------------.
     * |VOL +  | PLAY  | VOL - |
     * |-------+-------+-------|
     * |APP BCK| SPTLT |APP FWD|
     * `-----------------------'
     *
     */

    [_HOME] = LAYOUT_ortho_2x3(
        KC_VOLD, KC_MPLY, KC_VOLU,
        RSG(KC_TAB), LCMD(KC_SPC), LCMD(KC_TAB)
    ),

    /*
     *
     * ,-----------------------.
     * | COPY  |PREVIEW| PASTE |
     * |-------+-------+-------|
     * |CODEBLK| LINK  |HEADER |
     * `-----------------------'
     *
     */

    [_DRAFTS] = LAYOUT_ortho_2x3(
        LCMD(KC_C), LAG(KC_P), LCMD(KC_V),
        LCMD(KC_SLSH), LCMD(KC_K), LCTL(LCMD(KC_H))
    ),

    /*
     *
     * ,-----------------------.
     * | UNDO  |CNTR VU| REDO  |
     * |-------+-------+-------|
     * |DELETE | SEARCH|DESLCT |
     * `-----------------------'
     *
     */

    [_SHAPR3D] = LAYOUT_ortho_2x3(
        LCMD(KC_Z), LCMD(KC_1), SCMD(KC_Z),
        KC_DEL,     LCMD(KC_F), KC_ESC
    ),

/*
     *
     * ,-----------------------.
     * | UNDO  | ERASER| REDO  |
     * |-------+-------+-------|
     * |COLOR 1|COLOR 2|COLOR 3|
     * `-----------------------'
     *
     */

    [_PIXELSTUDIO] = LAYOUT_ortho_2x3(
        KC_Z, KC_E, KC_Y,
        KC_1, KC_2, KC_3
    )
};
