#ifdef AUTO_SHIFT_ENABLE
#include "vnoiram_auto_shift.h"

uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
    // if ( ( get_mods() & MOD_BIT(KC_LCTL) ) || ( get_mods() & MOD_BIT(KC_LSFT) )) {
    //     return get_generic_autoshift_timeout() - 15 ;
    // } else {
    //     return get_generic_autoshift_timeout();
    // }
    switch(keycode) {
        case AUTO_SHIFT_SPECIAL:
            return get_generic_autoshift_timeout();
        default:
        return get_generic_autoshift_timeout() - 15 ;
    }
    // official site sample
    // switch(keycode) {
    //     case AUTO_SHIFT_NUMERIC:
    //         return 2 * get_generic_autoshift_timeout();
    //     case AUTO_SHIFT_SPECIAL:
    //         return get_generic_autoshift_timeout() + 50;
    //     case AUTO_SHIFT_ALPHA:
    //     default:
    //         return get_generic_autoshift_timeout();
    // }
}
#endif
