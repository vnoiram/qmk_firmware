#include QMK_KEYBOARD_H
#include "vnoiram_keycodes.h"
#include "vnoiram_layer_enum.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif
#include "vnoiram_alt_tab.h"

/* ---------------------------------------------------------------
 * ALT_TAB_ENABLE: flag-based implementation (original)
 * --------------------------------------------------------------- */
#ifdef ALT_TAB_ENABLE

void proc_alt_tab(keyrecord_t *record, uint16_t regist_keycode, bool is_end) {
    if (record->event.pressed) {
#ifdef CONSOLE_ENABLE
        print("alttab tap alt tab\n");
#endif
        tap_code16(regist_keycode);
        if (is_end) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        } else {
            my_alt_tab_timer = timer_read();
        }
    }
}

bool process_record_user_alt_tab(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    register_code(KC_LALT);
#ifdef CONSOLE_ENABLE
                    print("alttab kc lalt\n");
#endif
                } else {
                    register_code(KC_TAB);
#ifdef CONSOLE_ENABLE
                    print("alttab kc tab\n");
#endif
                }
                my_alt_tab_timer = timer_read();
            } else {
                if (!is_alt_tab_active) {
                    if (timer_elapsed(my_alt_tab_timer) < ALT_TAB_TIMEOUT) {
#ifdef CONSOLE_ENABLE
                        print("alttab alt tab layer is on\n");
#endif
                        is_alt_tab_active = true;
                        tap_code(KC_TAB);
                    } else {
                        unregister_code(KC_LALT);
                    }
                } else {
                    unregister_code(KC_TAB);
                }
            }
            return false;
    }

    if (is_alt_tab_active) {
        switch (keycode) {
            case KC_H:
                proc_alt_tab(record, KC_LEFT, false);
                return false;
            case KC_J:
                proc_alt_tab(record, KC_DOWN, false);
                return false;
            case KC_K:
                proc_alt_tab(record, KC_UP, false);
                return false;
            case KC_L:
                proc_alt_tab(record, KC_RGHT, false);
                return false;
            case KC_ENT:
            case LT(_RNUM, KC_ENT):
                proc_alt_tab(record, KC_ENT, true);
                return false;
            case KC_ESC:
            default:
                proc_alt_tab(record, KC_ESC, true);
                return false;
        }
    }

    return true;
}

void matrix_scan_user_alt_tab(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(my_alt_tab_timer) > 1000) {
#ifdef CONSOLE_ENABLE
            print("alttab disable alt_tab\n");
#endif
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}

#endif /* ALT_TAB_ENABLE */

/* ---------------------------------------------------------------
 * ALT_TAB_BY_LAYER_ENABLE: layer-based implementation
 * - _ALTTAB layer maps H/J/K/L → KC_LEFT/DOWN/UP/RGHT
 * - H/J/K/L and MY_ALT_TAB extend the timer; other keys cancel
 * --------------------------------------------------------------- */
#ifdef ALT_TAB_BY_LAYER_ENABLE

bool process_record_user_alt_tab(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_ALT_TAB:
            if (record->event.pressed) {
                if (!layer_state_is(_ALTTAB)) {
                    register_code(KC_LALT);
                } else {
                    register_code(KC_TAB);
                }
                my_alt_tab_timer = timer_read();
            } else {
                if (!layer_state_is(_ALTTAB)) {
                    if (timer_elapsed(my_alt_tab_timer) < ALT_TAB_TIMEOUT) {
                        layer_on(_ALTTAB);
                        tap_code(KC_TAB);
                    } else {
                        unregister_code(KC_LALT);
                    }
                } else {
                    unregister_code(KC_TAB);
                }
            }
            return false;

        case KC_ENT:
            if (layer_state_is(_ALTTAB) && record->event.pressed) {
                unregister_code(KC_LALT);
                layer_off(_ALTTAB);
                return false;
            }
            break;

        case KC_LEFT:
        case KC_DOWN:
        case KC_UP:
        case KC_RGHT:
            // layer handles HJKL → arrows; only extend timer here
            if (layer_state_is(_ALTTAB) && record->event.pressed) {
                my_alt_tab_timer = timer_read();
            }
            break;

        default:
            if (layer_state_is(_ALTTAB) && record->event.pressed) {
                tap_code(KC_ESC);
                unregister_code(KC_LALT);
                layer_off(_ALTTAB);
                return false;
            }
    }
    return true;
}

void matrix_scan_user_alt_tab(void) {
    if (layer_state_is(_ALTTAB)) {
        if (timer_elapsed(my_alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            layer_off(_ALTTAB);
        }
    }
}

#endif /* ALT_TAB_BY_LAYER_ENABLE */
