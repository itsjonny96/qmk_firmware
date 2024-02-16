/* Copyright 2021 BINEPAD 
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
#include "print.h"

bool is_cmd_tab_active = false; 
bool is_alt_tab_active = false; 
uint16_t cmd_tab_timer = 0;  
uint16_t alt_tab_timer = 0;  


enum custom_keycodes {
    LOCK_SCREEN = SAFE_RANGE,
    WINDOWS_LOCK_SCREEN,
    QUICK_ADD,
    CMD_TAB,
    CMD_TAB_INV,
    ALT_TAB,
    ALT_TAB_INV
};

const uint16_t PROGMEM lock_screen [] = {CMD_TAB_INV, LCMD(KC_F3), CMD_TAB, COMBO_END};
const uint16_t PROGMEM windows_lock_screen [] = {ALT_TAB_INV, LGUI(KC_D), ALT_TAB, COMBO_END};
const uint16_t PROGMEM switch_layer1 [] = {LCMD(KC_C), LCMD(KC_V), CMD_TAB_INV, CMD_TAB, COMBO_END};
const uint16_t PROGMEM switch_layer2 [] = {LCTL(KC_C), LCTL(KC_V), ALT_TAB_INV, ALT_TAB, COMBO_END};

combo_t key_combos[] = {
  COMBO(lock_screen, LOCK_SCREEN),
  COMBO(windows_lock_screen, WINDOWS_LOCK_SCREEN),
  COMBO(switch_layer1, TO(1)),
  COMBO(switch_layer1, TO(0)),
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   // If console is enabled, it will print the matrix position and status of each key pressed
// #ifdef CONSOLE_ENABLE
//     printf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
// #endif 
//   return true;
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QUICK_ADD:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LCMD) SS_DOWN(X_A) SS_UP(X_LCTL) SS_UP(X_LCMD) SS_UP(X_A));
            }
            return false;
         case LOCK_SCREEN:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LCMD) SS_DOWN(X_Q) SS_UP(X_LCTL) SS_UP(X_LCMD) SS_UP(X_Q));
            }
            return false; /* Skip all further processing of this key */
        case WINDOWS_LOCK_SCREEN:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_L) SS_UP(X_LGUI) SS_UP(X_L));
            }
            return false; /* Skip all further processing of this key */
        case CMD_TAB:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                register_code(KC_TAB);
                } else {
                unregister_code(KC_TAB);
                }
                return true;
                break;
        case CMD_TAB_INV:
            if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                    is_cmd_tab_active = true;
                    register_code(KC_LGUI);
                    register_code(KC_LSFT);
                }
                cmd_tab_timer = timer_read();
                register_code(KC_TAB);
                } else {
                unregister_code(KC_TAB);
                }
                return true;
                break;
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
                } else {
                unregister_code(KC_TAB);
                }
                return true;
                break;
        case ALT_TAB_INV:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                    register_code(KC_LSFT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
                } else {
                unregister_code(KC_TAB);
                }
                return true;
                break;
        default:
            return false;
    }
}

void matrix_scan_user(void) { // The very important timer.
  if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      unregister_code(KC_LSFT);
      is_cmd_tab_active = false;
    }
  }
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      unregister_code(KC_LSFT);
      is_alt_tab_active = false;
    }
  }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* LAYER 0               
     *
     * ,-----------------------.         
     * |       |       |       |                
     * |-------+-------+-------|
     * |       |       |       |               
     * |-------+-------+-------|
     * |   +   |   +   |   +   |  This combo locks the screen       
     * `-----------------------'               
     *
     * ,-----------------------.            
     * |  COPY |  MOOM | PASTE |                
     * |-------+-------+-------|
     * |CLS TAB|QCK ADD|NEW TAB|               
     * |-------+-------+-------|
     * |APP <- |CLR DSK|APP -> |               
     * `-----------------------'               
     */
    
	[0] = LAYOUT_ortho_3x3(
      LCMD(KC_C), SCMD(KC_UP), LCMD(KC_V), 
      LCMD(KC_W), QUICK_ADD, LCMD(KC_T),
      CMD_TAB_INV, LCMD(KC_F3), CMD_TAB
    ),

	
/* LAYER 1
     *
     * ,-----------------------.         
     * |       |       |       |                
     * |-------+-------+-------|
     * |       |       |       |               
     * |-------+-------+-------|
     * |   +   |   +   |   +   |  This combo locks the screen       
     * `-----------------------'               
     *
     *
     * ,-----------------------.            
     * |  COPY |  MOOM | PASTE |                
     * |-------+-------+-------|
     * |CLS TAB|QCK ADD|NEW TAB|               
     * |-------+-------+-------|
     * |APP <- |CLR DSK|APP -> |               
     * `-----------------------'               
     */
    
    [1] = LAYOUT_ortho_3x3(
      LCTL(KC_C), LGUI(KC_UP), LCTL(KC_V), 
      LCTL(KC_W), LCTL(KC_SPC), LCTL(KC_T), 
      ALT_TAB_INV, LGUI(KC_D), ALT_TAB
    )
};

