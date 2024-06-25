#include "quantum_keycodes.h"
#include "quantum.h"
#include "vnoiram_tapping_term.h"
#include "vnoiram_layer_enum.h"

// tapping term per key
#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):
        case LSFT_T(KC_Z):
            return TAPPING_TERM + 1750;
        case LGUI_T(KC_X):
        case LALT_T(KC_C):
#ifdef TAP_DANCE_ENABLE
        // case TD_RESET:
        //     return TAPPING_TERM + 1050;
        // case TD_RBRC:
        //     return TAPPING_TERM + 300;
        // case TD_LBRC:
        //     return TAPPING_TERM + 270;
#endif
            return TAPPING_TERM + 1350;
        case LT(_ALTMOVE,KC_BSPC):
        case LCTL_T(KC_ESC):
        case LT(_SFT,KC_SPC):
        case LT(_SPCL,KC_ESC)
            return TAPPING_TERM - 85;
        case LT(_RNUM,KC_ENT):
            return TAPPING_TERM - 90;
        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef RETRO_TAPPING_PER_KEY
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_ALTMOVE,KC_BSPC):
        case LCTL_T(KC_ESC):
        case LT(_RNUM,KC_ENT):
        case LT(_SPCL,KC_ESC)
        case LT(_SFT,KC_SPC):
        case LCTL_T(KC_A):
        case LSFT_T(KC_Z):
        case LGUI_T(KC_X):
            return true;
        default:
            return false;
    }
}
#endif
