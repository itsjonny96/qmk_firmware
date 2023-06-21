/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

// enum my_keycodes {

// }

enum combos {
    BOOTKB
};

#define _HOME 0
#define _DRAFTS 1
#define _SHAPR3D 2
#define _PIXELSTUDIO 3   

const uint16_t PROGMEM boot_kb [] = {KC_VOLD, KC_VOLU, KC_MCTL, KC_LPAD, COMBO_END};

combo_t key_combos[] = {
  [BOOTKB] = COMBO(boot_kb, QK_BOOT),  // This combo will put the keyboard into DFU mode for flashing
};
// combo_t key_combos[COMBO_COUNT] = {
//     COMBO(boot_kb, QK_BOOT), // This combo will put the keyboard into DFU mode for flashing
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     *
     * ,-----------------------.
     * |VOL +  | PLAY  | VOL - |
     * |-------+-------+-------|
     * |MSN CTL| SPTLT |LNCHPD |
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
    )
};
