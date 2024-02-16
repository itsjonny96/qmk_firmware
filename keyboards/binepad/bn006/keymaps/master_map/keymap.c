/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H


#define _HOME 0
#define _OBSIDIAN 1
#define _SHAPR3D 2
#define _PIXELSTUDIO 3  

bool is_alt_tab_active = false; 
uint16_t alt_tab_timer = 0;     

enum custom_keycodes {          
  ALT_TAB = SAFE_RANGE,
  ALT_TAB_INV
};

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

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case _PIXELSTUDIO: 
                rgb_matrix_set_color(i, RGB_GREEN);
                break;
            case _SHAPR3D: 
                rgb_matrix_set_color(i, RGB_BLUE);
                break;    
            case _OBSIDIAN: 
                rgb_matrix_set_color(i, RGB_PURPLE);
                break;
            default:
                break;
        }
    }
    return false;
}

// COMBOS 

const uint16_t PROGMEM boot_kb [] = {KC_VOLD, KC_VOLU, ALT_TAB_INV, ALT_TAB, COMBO_END};
const uint16_t PROGMEM up_lyr1 [] = {KC_VOLU, ALT_TAB, COMBO_END};
const uint16_t PROGMEM up_lyr2 [] = {LCMD(KC_V), LCMD(KC_E), COMBO_END};
const uint16_t PROGMEM up_lyr3 [] = {SCMD(KC_Z), KC_ESC, COMBO_END};
const uint16_t PROGMEM up_lyr4 [] = {KC_Y, KC_3, COMBO_END};
const uint16_t PROGMEM dn_lyr4 [] = {KC_Z, KC_1, COMBO_END};
const uint16_t PROGMEM dn_lyr3 [] = {LCMD(KC_Z), KC_DEL, COMBO_END};
const uint16_t PROGMEM dn_lyr2 [] = {LCMD(KC_C), LOPT(KC_S), COMBO_END};
const uint16_t PROGMEM dn_lyr1 [] = {KC_VOLD, ALT_TAB_INV, COMBO_END};

combo_t key_combos[] = {
  [BOOTKB] = COMBO(boot_kb, QK_BOOT),  // This combo will put the keyboard into DFU mode for flashing
  [UPLYR_1] = COMBO(up_lyr1, TO(_OBSIDIAN)),
  [UPLYR_2] = COMBO(up_lyr2, TO(_SHAPR3D)),
  [UPLYR_3] = COMBO(up_lyr3, TO(_PIXELSTUDIO)),
  [UPLYR_4] = COMBO(up_lyr4, TO(_HOME)),
  [DNLYR_4] = COMBO(dn_lyr4, TO(_SHAPR3D)),
  [DNLYR_3] = COMBO(dn_lyr3, TO(_OBSIDIAN)),
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

// MACROS

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LGUI);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case ALT_TAB_INV:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LGUI);
          register_code(KC_LSFT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      unregister_code(KC_LSFT);
      is_alt_tab_active = false;
    }
  }
}


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
        ALT_TAB_INV, LCMD(KC_SPC), ALT_TAB
    ),

    /* 
     *
     * ,-----------------------.
     * | COPY  |CMD PLT| PASTE |
     * |-------+-------+-------|
     * |SOURCE |QK SWTC|READER |
     * `-----------------------'
     *
     */

    [_OBSIDIAN] = LAYOUT_ortho_2x3(
        LCMD(KC_C), LCMD(KC_P), LCMD(KC_V),
        LOPT(KC_S), LCMD(KC_O), LCMD(KC_E)
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
