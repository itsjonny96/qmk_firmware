#include QMK_KEYBOARD_H
 
 enum layers{
    Shapr3D,
    VSCode,
 };

// Light Layers

// const rgblight_segment_t PROGMEM layer_review[] = RGBLIGHT_LAYER_SEGMENTS(



//   );


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* LAYER 0
     * ,-----------------------.
     * |  UNDO |  MUTE | REDO  |  ENCODER - PRESS (MUTE) / KNOB (VOLUME CONTROL)
     * |-------+-------+-------|
     * |LEFT VU|CNTR VU|RGHT VU|
     * |-------+-------+-------|
     * |DELETE | SEARCH|DESLCT |
     * `-----------------------'
     */

    [Shapr3D] = LAYOUT_ortho_3x3(
      LCMD(KC_Z), TO(VSCode), SCMD(KC_Z),
      LCMD(KC_7), LCMD(KC_1), LCMD(KC_6),
      KC_DEL,     LCMD(KC_F), KC_ESC
      ),


    /* LAYER 1
     * ,-----------------------.
     * |       |       |       |  ENCODER - PRESS (NA) / KNOB (Hue Control)
     * |-------+-------+-------|
     * |       |       |       |
     * |-------+-------+-------|
     * |       |       |       |
     * `-----------------------'
     */

    [VSCode] = LAYOUT_ortho_3x3(
      _______, _______, _______,
      _______, _______, _______,
      _______, _______, _______
      )

};

bool encoder_update_user(uint8_t index, bool clockwise) {

  switch (get_highest_layer(layer_state)) {
      case 1:
          if (clockwise) {
              tap_code16(KC_WH_U);
          } else {
              tap_code16(KC_WH_D);
          }
          break;
      default:
          if (clockwise) {
              tap_code16(KC_WH_U);
          } else {
              tap_code16(KC_WH_D);
          }
          break;

  }
    return true;
}
