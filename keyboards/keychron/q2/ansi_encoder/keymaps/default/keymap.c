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

enum layers{
    MAC_BASE,
    WIN_BASE,
    _FN1,
    _FN2,
    _FN3
};

enum custom_keycodes {
    KC_MISSION_CONTROL = SAFE_RANGE,
    KC_LAUNCHPAD,
    KC_LOCK_SCREEN,
};

// MACROS

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
    default: 
       return true; /* Process all other keycodes normally */
      }
}

// COMBOS

const uint16_t PROGMEM grave_ctrl [] = {MO(_FN1), MO(_FN3), COMBO_END};
const uint16_t PROGMEM screen_lock_mac [] = {KC_Z, KC_X, KC_C, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  COMBO(screen_lock_mac, KC_LOCK_SCREEN), 
  COMBO(grave_ctrl, KC_LCTL),     // Pressing these two keys at the same time will activate a grave control function while maintaining individual function keys
};

#define KC_WAVE S(KC_GRV)
#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)
#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_67(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,            KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,            KC_RSFT, KC_UP,
        KC_LCTL, KC_LOPT, KC_LCMD,                            KC_SPC,                             KC_RCMD, MO(_FN1), MO(_FN3), KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_ansi_67(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,    KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,   KC_BSLS,          KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,             KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN2), MO(_FN3),  KC_LEFT, KC_DOWN, KC_RGHT),

    [_FN1] = LAYOUT_ansi_67(
        KC_GRV,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, RGB_VAD, RGB_VAI, _______, _______, KC_MPRV, KC_MNXT, KC_VOLD,  KC_VOLU,   _______,          _______,
        RGB_TOG, RGB_MOD, KC_UP,   RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, KC_MPLY, _______,  _______,   _______,          KC_PAGE_UP,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______,             KC_PGUP,          KC_PAGE_DOWN,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             KC_PGDN, _______,
        _______, _______, _______,                            _______,                            _______, _______,  _______,   KC_WH_L, _______, KC_WH_R),

    [_FN2] = LAYOUT_ansi_67(
        KC_GRV,  KC_BRID, KC_BRIU, KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,  KC_VOLU,   _______,          _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______,  _______,   _______,          _______,
        _______, RGB_RMOD,RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______,             _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             _______, _______,
        _______, _______, _______,                            _______,                            _______, _______,  _______,   _______, _______, _______),

    [_FN3] = LAYOUT_ansi_67(
        KC_WAVE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,    _______,          _______,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______,  _______,   _______,          KC_BTN3,
        _______, RGB_RMOD,RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, _______, _______, _______, _______,             KC_HOME,           KC_END,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              KC_END, LCMD(KC_UP),
        _______, _______, _______,                            _______,                            _______, _______,  _______,   _______, LCMD(KC_DOWN), _______)
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    
  switch (get_highest_layer(layer_state)) {
      case MAC_BASE:
          if (clockwise) {
              tap_code(KC_VOLU); //VOLUME UP 
          } else {
              tap_code(KC_VOLD); // VOLUME DOWN
          }
          break;
      case _FN3:
          if (clockwise) {
              tap_code16(C(KC_TAB)); //TAB FORWARD IN SAFARI 
          } else {
              tap_code16(RCS(KC_TAB)); //TAB BACKWARDS IN SAFARI 
          }
          break;
          
  }
    return false;

}
