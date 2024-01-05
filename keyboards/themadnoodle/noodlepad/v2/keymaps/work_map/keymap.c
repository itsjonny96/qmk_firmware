#include QMK_KEYBOARD_H
 
 enum layers{
    Main,
 };

// Light Layers

// const rgblight_segment_t PROGMEM layer_review[] = RGBLIGHT_LAYER_SEGMENTS(



//   );


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* MAIN
     * ,-----------------------.
     * |  COPY |       | PASTE |  ENCODER - PRESS (MUTE) / KNOB (VOLUME CONTROL)
     * |-------+-------+-------|
     * |       |       |       |
     * |-------+-------+-------|
     * |       |       |       |
     * `-----------------------'
     */

    [Shapr3D] = LAYOUT_ortho_3x3(
      LCTL(KC_C), _______, LCTL(KC_V),
      _______, _______, _______,
      _______, _______, _______
      ),


    /* LAYER 1
     * ,-----------------------.
     * |       |       |       |  ENCODER - PRESS (NA) / KNOB (Hue Control)
     * |-------+-------+-------|
     * |       |CMD PLT|       |
     * |-------+-------+-------|
     * |       |       |       |
     * `-----------------------'
     */

    [VSCode] = LAYOUT_ortho_3x3(
      _______, _______, _______,
      _______, LCS(KC_P), _______,
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
