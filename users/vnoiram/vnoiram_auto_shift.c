/* ---------------------------------------------------------------
 * AUTO_SHIFT_ENABLE: QMK 標準 (現状維持)
 * --------------------------------------------------------------- */
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
#endif /* AUTO_SHIFT_ENABLE */

/* ---------------------------------------------------------------
 * MINE_AUTO_SHIFT_ENABLE: 自前 hold-detect (対象キー限定)
 * JTU ON 時は process_record_user_jtu 経由で送出して JTU 変換を通す
 * KC_TAB は LT との競合を避けるため対象外
 * --------------------------------------------------------------- */
#ifdef MINE_AUTO_SHIFT_ENABLE
#include "quantum.h"
#ifdef JTU_ENABLE
#include "jtu_custom_keycodes.h"
#endif

static uint16_t mine_as_key  = KC_NO;
static uint16_t mine_as_time = 0;
#define MINE_AS_TIMEOUT 90

static void mine_as_send(uint16_t kc, bool shifted) {
    keyrecord_t fake = {0};
    fake.event.pressed = true;
    if (shifted) add_mods(MOD_BIT(KC_LSFT));
    bool handled = false;
#ifdef JTU_ENABLE
    handled = !process_record_user_jtu(kc, &fake);
#endif
    if (!handled) {
        tap_code(kc);
    }
    if (shifted) del_mods(MOD_BIT(KC_LSFT));
}

bool process_record_user_auto_shift(uint16_t kc, keyrecord_t *r) {
    switch (kc) {
        case KC_SCLN: case KC_COMM: case KC_DOT:  case KC_SLSH:
        case KC_QUOT: case KC_MINS: case KC_GRV:  case KC_EQL:
        case KC_LBRC: case KC_RBRC: case KC_BSLS:
            if (r->event.pressed) {
                mine_as_key  = kc;
                mine_as_time = timer_read();
                return false;
            }
            if (mine_as_key == kc) {
                mine_as_send(kc, timer_elapsed(mine_as_time) >= MINE_AS_TIMEOUT);
                mine_as_key = KC_NO;
                return false;
            }
            break;
        default:
            if (mine_as_key != KC_NO) {
                mine_as_send(mine_as_key, false);
                mine_as_key = KC_NO;
            }
    }
    return true;
}
#endif /* MINE_AUTO_SHIFT_ENABLE */
