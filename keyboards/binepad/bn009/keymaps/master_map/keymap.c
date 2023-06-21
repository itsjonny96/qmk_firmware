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


enum my_keycodes {
    KC_MISSION_CONTROL = SAFE_RANGE,
    KC_LAUNCHPAD,
    KC_LOCK_SCREEN
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false; /* Skip all further processing of this key */

        case KC_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false; /* Skip all further processing of this key */

         case KC_LOCK_SCREEN:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LCMD) SS_DOWN(X_Q) SS_UP(X_LCTL) SS_UP(X_LCMD) SS_UP(X_Q));
            }
            return false; /* Skip all further processing of this key */
        default: 
            return true; /* Process all other keycodes normally */

    }
}


const uint16_t PROGMEM one_shot_layer1 [] = {C(KC_LEFT), LCMD(KC_SPC), COMBO_END};
const uint16_t PROGMEM one_shot_layer2 [] = {LCMD(KC_SPC), C(KC_RIGHT), COMBO_END};
const uint16_t PROGMEM previous_track [] = {KC_MISSION_CONTROL, LCMD(KC_C), COMBO_END};
const uint16_t PROGMEM next_track [] = {KC_LAUNCHPAD, LCMD(KC_V), COMBO_END};
const uint16_t PROGMEM lock_screen [] = {C(KC_LEFT), LCMD(KC_SPC), C(KC_RGHT), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
	COMBO(one_shot_layer1, OSL(1)),		// This will enable layer 1 in one shot mode
	COMBO(one_shot_layer2, OSL(2)),		// This will enable layer 2 in one shot mode
    COMBO(previous_track, KC_MPRV),     // Previous track 
    COMBO(next_track, KC_MNXT),         // Next track
    COMBO(lock_screen, KC_LOCK_SCREEN), // This combo will lock the screen 
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* LAYER 0
     * ,-----------------------.         
     * |       |       |       |                
     * |-------+-------+-------|
     * |       |       |       |               
     * |-------+-------+-------|
     * |   +   |   +   |       |  This combo enables layer 1 in one shot mode       
     * `-----------------------'              
     *
     * ,-----------------------.         
     * |       |       |       |                
     * |-------+-------+-------|
     * |       |       |       |               
     * |-------+-------+-------|
     * |       |   +   |   +   |  This combo enables layer 2 in one shot mode       
     * `-----------------------'               
     *
     * ,-----------------------.         
     * |       |       |   +   |                
     * |-------+-------+-------|
     * |       |       |   +   |               
     * |-------+-------+-------|
     * |       |       |       |  This combo enables next track       
     * `-----------------------'               
     *
     * ,-----------------------.         
     * |   +   |       |       |                
     * |-------+-------+-------|
     * |   +   |       |       |               
     * |-------+-------+-------|
     * |       |       |       |  This combo enables previous track        
     * `-----------------------'               
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
     * |MSN CTL|  PLAY |LNCHPAD|               
     * |-------+-------+-------|
     * |<- DSK | SPTLT |  DSK->|               
     * `-----------------------'               
     */
    
	[0] = LAYOUT(
      LCMD(KC_C), SCMD(KC_UP), LCMD(KC_V), 
      KC_MISSION_CONTROL, KC_MPLY, KC_LAUNCHPAD,
      C(KC_LEFT), LCMD(KC_SPC), C(KC_RGHT)
      ),

	
/* LAYER 1
     * ,-----------------------.
     * |  COPY |LK SCRN| PASTE |  
     * |-------+-------+-------|
     * |SCRNSHT|QK DRFT| SLEEP |
     * |-------+-------+-------|
     * | QUIT  |  PREF |MINIMIZ|
     * `-----------------------'
     */
    
    [1] = LAYOUT(
      LCMD(KC_C), KC_LOCK_SCREEN, LCMD(KC_V), 
      SCMD(KC_3), SCMD(KC_2), KC_SLEP, 
      LCMD(KC_Q), LCMD(KC_COMM), LCMD(KC_M)
      ),

	
/* LAYER 2 (SAFARI)
     * ,-----------------------.
     * |  COPY |NEW TAB| PASTE |  
     * |-------+-------+-------|
     * |TAB PRV|TAB VU |TAB FWD|
     * |-------+-------+-------|
     * |+RD LST| SEARCH|DEL TAB|
     * `-----------------------'
     */
    
    [2] = LAYOUT(
      LCMD(KC_C), LCMD(KC_T), LCMD(KC_V), 
      RCS(KC_TAB), SCMD(KC_BSLS), C(KC_TAB), 
      RCS(KC_D), LCMD(KC_F), LCMD(KC_W)
      )

};
