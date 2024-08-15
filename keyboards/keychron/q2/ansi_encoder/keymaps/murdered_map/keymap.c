 /* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers{
    MAC_BASE,
    WIN_BASE,
    _FN1,
    _FN2,
    _FN3
};

#define KC_SPFL KC_SUPER_FILL
#define KC_DATH KC_DUAL_AUTH
#define KC_DCVC KC_DCV_CONNECT

// COMBOS

const uint16_t PROGMEM grave_ctrl [] = {MO(_FN1), MO(_FN3), COMBO_END};
const uint16_t PROGMEM screen_lock_mac [] = {KC_Z, KC_X, KC_C, COMBO_END};

combo_t key_combos[] = {
  COMBO(screen_lock_mac, KC_LOCK_SCREEN), 
  COMBO(grave_ctrl, KC_LCTL),     // Pressing these two keys at the same time will activate a grave control function while maintaining individual function keys
};



//LIGHTING

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }
    if (get_highest_layer(layer_state) == 0) {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 255, 0, 0); // assuming caps lock is at led #5
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 0, 0);
    }
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_BLUE);
                }
            }
        }

    }
    return false;
}

// KEYMAP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_67(
        QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_HOME,
        KC_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,            KC_ENT,           KC_END,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,            KC_RSFT, KC_UP,
        KC_LCTL,  KC_LOPT, KC_LCMD,                            KC_SPC,                             KC_RCMD, MO(_FN1), MO(_FN3), KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_ansi_67(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,    KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,   KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,             KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN2), MO(_FN3),  KC_LEFT, KC_DOWN, KC_RGHT),

    [_FN1] = LAYOUT_ansi_67(
        KC_GRV,  _______, _______, KC_MCTL, KC_LPAD, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_VOLD,  KC_VOLU,    KC_DEL,          _______,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______,  _______,   _______,          KC_PAGE_UP,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,             KC_PGUP,          KC_PAGE_DOWN,
        _______,         RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,             KC_PGDN, _______,
        _______, _______, _______,                            _______,                            _______, _______,  _______,   KC_WH_L, _______, KC_WH_R),

    [_FN2] = LAYOUT_ansi_67(
        KC_GRV,  KC_BRID, KC_BRIU, KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU,   _______,          _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______,  _______,   _______,          _______,
        _______, RGB_RMOD,RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______,             _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
        _______, _______, _______,                            _______,                            _______, _______,  _______,   _______, _______, _______),

    [_FN3] = LAYOUT_ansi_67(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,    _______,          _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______,  _______,   _______,          KC_HOME,
        _______, KC_WH_L, RGB_VAD, KC_WH_R, RGB_SAD, RGB_SPD, _______, _______, KC_DATH, _______, _______, _______,             KC_HOME,           KC_END,
        _______,          _______, _______, KC_DCVC, KC_SPFL, _______, _______, _______, _______, _______, _______,             KC_END,  LCMD(KC_UP),
        _______, _______, _______,                            _______,                            _______, _______,  _______,   _______, LCMD(KC_DOWN), _______)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN1]     = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_FN2]     = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [_FN3]     = { ENCODER_CCW_CW(RCS(KC_TAB), C(KC_TAB)) },
};
#endif

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     if (!process_record_keychron(keycode, record)) {
//         return false;
//     }

//     return true;
// }

bool super_fill_key_down = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LOCK_SCREEN:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LCMD) SS_DOWN(X_Q) SS_UP(X_LCTL) SS_UP(X_LCMD) SS_UP(X_Q));
            }
            return false; /* Skip all further processing of this key */
        case KC_DUAL_AUTH:
            if (record->event.pressed) {
                SEND_STRING("kinit -f && mwinit -o");
            }
            return false;
        case KC_DCV_CONNECT:
            if (record->event.pressed) {
                SEND_STRING("python C:\\Users\\joyajj\\dcv\\dcv-cdd.py connect joyajj-clouddesk.aka.corp.amazon.com");
            }
            return false;  
        case KC_SUPER_FILL: {
            if (record->event.pressed) {
                super_fill_key_down = true;
            } else { // Release the key
                super_fill_key_down = false;
            }
            return true;
            break;
            }
        default:
            return true;  // Process all other keycodes normally
    }
}

#define REPEAT_DELAY 250
#define REPEAT_TERM 

void matrix_scan_user(void) {
  if (super_fill_key_down) {
    SEND_STRING(SS_TAP(X_TAB) SS_TAP(X_TAB) SS_TAP(X_TAB) SS_TAP(X_TAB) SS_DOWN(X_LCTL) SS_DOWN(X_V) SS_UP(X_LCTL) SS_UP(X_V));
  } else {
  }
}
