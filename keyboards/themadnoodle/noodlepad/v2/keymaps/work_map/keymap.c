#include QMK_KEYBOARD_H
 
 enum layers{
    Main,
 };

//LIGHTING

// const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {6, 4, HSV_RED},       // Light 4 LEDs, starting with LED 6
//     {12, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12

// const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {9, 2, HSV_CYAN}
// );
// // Light LEDs 11 & 12 in purple when keyboard layer 2 is active
// const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {11, 2, HSV_PURPLE}
// );
// // Light LEDs 13 & 14 in green when keyboard layer 3 is active
// const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {13, 2, HSV_GREEN}

// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//     my_capslock_layer,
//     my_layer1_layer,    // Overrides caps lock layer
//     my_layer2_layer,    // Overrides other layers
//     my_layer3_layer     // Overrides other layers
// );

// void keyboard_post_init_user(void) {
//     // Enable the LED layers
//     rgblight_layers = my_rgb_layers;
// }

// layer_state_t layer_state_set_user(layer_state_t state) {

// rgblight_set_layer_state(1, layer_state_cmp(state, 1));

// rgblight_set_layer_state(2, layer_state_cmp(state, 2));

// rgblight_set_layer_state(0, layer_state_cmp(state, 3));

// return state;

// }

// bool led_update_user(led_t led_state) {

// rgblight_set_layer_state(3, led_state.caps_lock);

// return true;

// }


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* MAIN
     * ,-----------------------.
     * |  COPY |       | PASTE |  ENCODER - PRESS (MUTE) / KNOB (VOLUME CONTROL)
     * |-------+-------+-------|
     * |       | SEARCH|       |
     * |-------+-------+-------|
     * |       |       |       |
     * `-----------------------'
     */

    [Shapr3D] = LAYOUT_ortho_3x3(
      LCTL(KC_C), _______, LCTL(KC_V),
      _______, LGUI(KC_S), _______,
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
