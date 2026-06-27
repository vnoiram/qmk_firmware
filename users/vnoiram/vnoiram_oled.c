#ifdef OLED_ENABLE
#include "quantum.h"
#include "lib/oledkit/oledkit.h"

#if defined(MASTER_RIGHT) || defined(MASTER_LEFT)
#include "lib/keyball/keyball.h"
#include "vnoiram_layer_enum.h"

/* Override logo render to empty so LTO drops logo drawing code */
void oledkit_render_logo_user(void) { }

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        oled_off();
        return false;
    }
    oledkit_render_info_user();
    return true;
}

void oledkit_render_info_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _DEFAULT_KEY:  oled_write_P(PSTR("NORMAL"), false); break;
        case _DEFAULT_MICE: oled_write_P(PSTR("MICE  "), false); break;
        case _SFT:          oled_write_P(PSTR("SFT   "), false); break;
        case _SPCL:         oled_write_P(PSTR("SPCL  "), false); break;
        case _SCRL:         oled_write_P(PSTR("SCRL  "), false); break;
        case _RNUM:         oled_write_P(PSTR("RNUM  "), false); break;
#ifdef ALT_TAB_BY_LAYER_ENABLE
        case _ALTTAB:       oled_write_P(PSTR("ALTTAB"), false); break;
#endif
        default:            oled_write_P(PSTR("OTHER "), false); break;
    }
    oled_advance_page(true);

    uint8_t cpi = keyball_get_cpi();
    oled_write_P(PSTR("CPI "), false);
    oled_write_char('0' + cpi / 10, false);
    oled_write_char('0' + cpi % 10, false);
    oled_write_P(PSTR("00"), false);
    oled_advance_page(true);

    oled_write_P(keyball_get_scroll_mode() ? PSTR("SCR ON ") : PSTR("SCR OFF"), false);
    oled_write_P(PSTR(" DIV "), false);
    oled_write_char('0' + keyball_get_scroll_div(), false);
}

#else
/* Fallback: MASTER not defined, both OLEDs show info */
#include "lib/keyball/keyball.h"
#include "vnoiram_layer_enum.h"

void oledkit_render_info_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _DEFAULT_KEY:  oled_write_P(PSTR("NORMAL"), false); break;
        case _DEFAULT_MICE: oled_write_P(PSTR("MICE  "), false); break;
        case _SFT:          oled_write_P(PSTR("SFT   "), false); break;
        case _SPCL:         oled_write_P(PSTR("SPCL  "), false); break;
        case _SCRL:         oled_write_P(PSTR("SCRL  "), false); break;
        case _RNUM:         oled_write_P(PSTR("RNUM  "), false); break;
#ifdef ALT_TAB_BY_LAYER_ENABLE
        case _ALTTAB:       oled_write_P(PSTR("ALTTAB"), false); break;
#endif
        default:            oled_write_P(PSTR("OTHER "), false); break;
    }
    oled_advance_page(true);

    uint8_t cpi = keyball_get_cpi();
    oled_write_P(PSTR("CPI "), false);
    oled_write_char('0' + cpi / 10, false);
    oled_write_char('0' + cpi % 10, false);
    oled_write_P(PSTR("00"), false);
    oled_advance_page(true);

    oled_write_P(keyball_get_scroll_mode() ? PSTR("SCR ON ") : PSTR("SCR OFF"), false);
    oled_write_P(PSTR(" DIV "), false);
    oled_write_char('0' + keyball_get_scroll_div(), false);
}

#endif /* MASTER_RIGHT / MASTER_LEFT / else */

#endif /* OLED_ENABLE */
