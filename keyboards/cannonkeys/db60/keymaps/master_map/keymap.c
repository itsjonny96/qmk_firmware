/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

// CUSTOM KEYCODES

enum my_keycodes {
    KC_LOCK_SCREEN = SAFE_RANGE,
    KC_SUPER_FILL,
    KC_DUAL_AUTH,
    KC_DCV_CONNECT,
};


#define KC_SPFL KC_SUPER_FILL
#define KC_DATH KC_DUAL_AUTH
#define KC_DCVC KC_DCV_CONNECT

#define _BASE 0
#define _FN1 1
#define _MACROS 2



// MACROS

bool super_fill_key_down = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

  case KC_LOCK_SCREEN:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LCMD) SS_DOWN(X_Q) SS_UP(X_LCTL) SS_UP(X_LCMD) SS_UP(X_Q));
            }
            return false; /* Skip all further processing of this key */
   case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
    case KC_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
    case KC_DUAL_AUTH:
            if (record->event.pressed) {
                SEND_STRING("kinit -f && mwinit -o");
            }
            return false;
    case KC_DCV_CONNECT:
            if (record->event.pressed) {
                SEND_STRING("python C:\\Users\\joyajj\\dcv-cdd.py connect joyajj-clouddesk.aka.corp.amazon.com");
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
            return true; /* Process all other keycodes normally */
      }
}


// TIMER

#define REPEAT_DELAY 250
#define REPEAT_TERM 15

void matrix_scan_user(void) {
  if (super_fill_key_down) {
    SEND_STRING(SS_TAP(X_TAB) SS_TAP(X_TAB) SS_TAP(X_TAB) SS_TAP(X_TAB) SS_DOWN(X_LCTL) SS_DOWN(X_V) SS_UP(X_LCTL) SS_UP(X_V));
  } else {
  }
}

// COMBOS

const uint16_t PROGMEM screen_lock_mac [] = {KC_Z, KC_X, KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  COMBO(screen_lock_mac, KC_LOCK_SCREEN), 
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_60_ansi(
    QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    KC_RSFT,
    KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                        KC_RGUI, MO(_FN1), MO(_MACROS), KC_RCTL
  ),

  [_FN1] = LAYOUT_60_ansi(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,  KC_DEL,
    _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______, _______, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PGUP,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   KC_PGDN,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______
  ), 
  
  [_MACROS] = LAYOUT_60_ansi(
  	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, KC_DATH, _______, _______, _______,          KC_HOME,
    _______, _______, _______, KC_DCVC, KC_SPFL, _______, _______, _______, _______, _______, _______,                   KC_END,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______
  )
};
