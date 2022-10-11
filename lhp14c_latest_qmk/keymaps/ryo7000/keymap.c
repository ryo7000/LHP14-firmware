#include QMK_KEYBOARD_H
#include "joystick.h"
#include "analog.h"

#define DEFAULT 0
#define WASD 1

static int actuation = 256; // actuation point for arrows (0-511)
bool arrows[4];

void render_logo(void) {
    oled_set_cursor(0, 0);
    oled_write_P(lhp_logo, false);
}



void render_layer(void) {
    oled_set_cursor(START_COL, START_ROW);
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case DEFAULT:
            oled_write_P(PSTR("Default\n"), false);
            rgblight_sethsv(68, 15, 150);
            break;
        case WASD:
            oled_write_P(PSTR("WASD\n"), false);
            rgblight_sethsv(20, 255, 210);
            break;

        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

bool oled_task_user(void) {
    render_logo();
    render_layer();
    return false;
}





void suspend_power_down_kb(void) {
    oled_off();
}

void suspend_wakeup_init_kb(void) {
    oled_on();
}



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [DEFAULT] = LAYOUT( \
    LCTL(KC_1),  LCTL(KC_2),  LCTL(KC_3),  LCTL(KC_4),  LCTL(KC_5),  LCTL(KC_6),  LCTL(KC_7), \
    LALT(KC_1),  LALT(KC_2),  LALT(KC_3),  LALT(KC_4),  LALT(KC_5),  LALT(KC_6),  LALT(KC_7), \
    LSFT(KC_2),  LSFT(KC_2),  LSFT(KC_3),  LSFT(KC_4),  LSFT(KC_5),  LSFT(KC_6),  TO(WASD),   \
    LCTL(KC_8),  LCTL(KC_9),  LCTL(KC_0),  LALT(KC_8),  LALT(KC_9),                           \
                                                                     LSFT(KC_1),  JS_BUTTON7, \
                                                                                  LSFT(KC_7)  \
   ),
   [WASD] = LAYOUT( \
    LCTL(KC_1),  LCTL(KC_2),  LCTL(KC_3),  LCTL(KC_4),  LCTL(KC_5),  LCTL(KC_6),  LCTL(KC_7), \
    LALT(KC_1),  LALT(KC_2),  LALT(KC_3),  LALT(KC_4),  LALT(KC_5),  LALT(KC_6),  LALT(KC_7), \
    LSFT(KC_2),  LSFT(KC_2),  LSFT(KC_3),  LSFT(KC_4),  LSFT(KC_5),  LSFT(KC_6),  TO(DEFAULT), \
    LCTL(KC_8),  LCTL(KC_9),  LCTL(KC_0),  LALT(KC_8),  LALT(KC_9),                           \
                                                                     LSFT(KC_1),  JS_BUTTON7, \
                                                                                  LSFT(KC_7)  \
    ),
};






joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL
};

void matrix_scan_user(void) {

    if (IS_LAYER_ON(DEFAULT)) {
        joystick_status.axes[0] = analogReadPin(F4)/4 - 128;
        joystick_status.axes[1] = analogReadPin(D4)/4 - 128;
        joystick_status.status |= JS_UPDATED;
    } else {
        if (!arrows[0] && analogReadPin(F4) - 512 > actuation){
            arrows[0] = true;
            register_code16(KC_D);
        }
        else if (arrows[0] &&  analogReadPin(F4) - 512 < actuation){
            arrows[0] = false;
            unregister_code16(KC_D);
        }
        if (!arrows[1] && analogReadPin(F4) - 512 < -actuation){
            arrows[1] = true;
            register_code16(KC_A);
        }
        else if (arrows[1] && analogReadPin(F4) - 512 > -actuation){
            arrows[1] = false;
            unregister_code16(KC_A);
        }
        if (!arrows[2] && analogReadPin(D4) - 512 > actuation){
            arrows[2] = true;
            register_code16(KC_S);
        }
        else if (arrows[2] &&  analogReadPin(D4) - 512 < actuation){
            arrows[2] = false;
            unregister_code16(KC_S);
        }
        if (!arrows[3] && analogReadPin(D4) - 512 < -actuation){
            arrows[3] = true;
            register_code16(KC_W);
        }
        else if (arrows[3] && analogReadPin(D4) - 512 > -actuation){
            arrows[3] = false;
            unregister_code16(KC_W); 
        }
        joystick_status.status |= JS_UPDATED;
    }
}



