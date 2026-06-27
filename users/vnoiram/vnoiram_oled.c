#ifdef OLED_ENABLE
#include "quantum.h"
#include "lib/oledkit/oledkit.h"
#include "jtu_custom_keycodes.h"
#include "vnoiram_oled.h"
#include "lib/keyball/keyball.h"

#if defined(MASTER_RIGHT) || defined(MASTER_LEFT)

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

#endif /* MASTER_RIGHT / MASTER_LEFT / else */

void oledkit_render_info_user(void) {
    oled_write(is_jtu_active ? PSTR("JTU ON ") : PSTR("JTU OFF "), false);

    uint8_t cpi = keyball_get_cpi();
    oled_write_P(PSTR("CPI "), false);
    oled_write_char('0' + cpi / 10, false);
    oled_write_char('0' + cpi % 10, false);
    oled_write_P(PSTR("00"), false);
    // oled_advance_page(true);

    // oled_write_P(keyball_get_scroll_mode() ? PSTR(" SCR ON      ") : PSTR(" SCR OFF    "), false);
    oled_write_P(PSTR(" DIV "), false);
    oled_write_char('0' + keyball_get_scroll_div(), false);
}

#endif /* OLED_ENABLE */
