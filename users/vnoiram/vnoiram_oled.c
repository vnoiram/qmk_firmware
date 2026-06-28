#ifdef MINE_OLED_ENABLE

#include "quantum.h"
#include "i2c_master.h"
#include "vnoiram_oled.h"
#include "jtu_custom_keycodes.h"
#include "lib/keyball/keyball.h"

#define OLED_ADDR    (0x3C << 1)
#define OLED_TIMEOUT 100

extern const unsigned char font[] PROGMEM;

static void ssd1306_set_pos(uint8_t page, uint8_t col) {
    uint8_t buf[4] = {
        0x00,
        0xB0 | (page & 0x07),
        0x00 | (col & 0x0F),
        0x10 | ((col >> 4) & 0x07),
    };
    i2c_transmit(OLED_ADDR, buf, 4, OLED_TIMEOUT);
}

static void ssd1306_write_char(char c) {
    uint8_t buf[7];
    buf[0] = 0x40;
    if (c == ' ') {
        memset(&buf[1], 0, 6);
    } else {
        memcpy_P(&buf[1], font + ((uint8_t)c - 0x30) * 6, 6);
    }
    i2c_transmit(OLED_ADDR, buf, 7, OLED_TIMEOUT);
}

static void ssd1306_write_str(const char *s) {
    while (*s) ssd1306_write_char(*s++);
}

void mine_oled_init(void) {
    i2c_init();

    if (!is_keyboard_master()) {
        uint8_t off[2] = {0x00, 0xAE};
        i2c_transmit(OLED_ADDR, off, 2, OLED_TIMEOUT);
        return;
    }

    // SSD1306 128x32 init (page addressing mode)
    static const uint8_t init_cmds[] PROGMEM = {
        0x00,       // command stream
        0xAE,       // display off
        0xD5, 0x80, // display clock divide/oscillator
        0xA8, 0x1F, // multiplex ratio (32 lines)
        0x40,       // display start line 0
        0x8D, 0x14, // charge pump enable
        0x20, 0x02, // page addressing mode
        0xA1,       // segment remap (mirror)
        0xC8,       // COM output scan direction reversed
        0xD3, 0x00, // display offset = 0
        0xDA, 0x02, // COM pins sequential (128x32)
        0x81, 0xFF, // contrast maximum
        0xD9, 0xF1, // pre-charge period
        0xDB, 0x20, // VCOMH deselect level
        0xA4,       // display follows RAM
        0xA6,       // normal (non-inverted)
        0x2E,       // deactivate scroll
        0xAF,       // display on
    };
    i2c_transmit_P(OLED_ADDR, init_cmds, sizeof(init_cmds), OLED_TIMEOUT);

    // Clear all 4 pages (8 bytes of zeros per transmit × 16 = 128 cols per page)
    uint8_t clr[9] = {0x40, 0, 0, 0, 0, 0, 0, 0, 0};
    for (uint8_t p = 0; p < 4; p++) {
        ssd1306_set_pos(p, 0);
        for (uint8_t i = 0; i < 16; i++) {
            i2c_transmit(OLED_ADDR, clr, sizeof(clr), OLED_TIMEOUT);
        }
    }
}

void mine_oled_render(void) {
    if (!is_keyboard_master()) return;

    ssd1306_set_pos(0, 0);
    // "JTU ON " or "JTU OFF" — both 7 chars, same column width
    ssd1306_write_str(is_jtu_active ? "JTU 1" : "JTU 0");
    ssd1306_write_str(" CPI ");
    uint8_t cpi = keyball_get_cpi();
    ssd1306_write_char('0' + cpi / 10);
    ssd1306_write_char('0' + cpi % 10);
    ssd1306_write_str("00 DIV ");
    ssd1306_write_char('0' + keyball_get_scroll_div());
    ssd1306_write_char(' ');
}

#elif defined(OLED_ENABLE)

#include "quantum.h"
#include "lib/oledkit/oledkit.h"
#include "jtu_custom_keycodes.h"
#include "vnoiram_oled.h"
#include "lib/keyball/keyball.h"

#if defined(MASTER_RIGHT) || defined(MASTER_LEFT)

void oledkit_render_logo_user(void) { }

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        oled_off();
        return false;
    }
    oledkit_render_info_user();
    return true;
}

#endif /* MASTER_RIGHT / MASTER_LEFT */

void oledkit_render_info_user(void) {
    oled_write(is_jtu_active ? PSTR("JTU 1 ") : PSTR("JTU 0 "), false);

    uint8_t cpi = keyball_get_cpi();
    oled_write_P(PSTR("CPI "), false);
    oled_write_char('0' + cpi / 10, false);
    oled_write_char('0' + cpi % 10, false);
    oled_write_P(PSTR("00"), false);

    oled_write_P(PSTR(" DIV "), false);
    oled_write_char('0' + keyball_get_scroll_div(), false);
    oled_write_P(PSTR(" "), false);
}

#endif /* MINE_OLED_ENABLE / OLED_ENABLE */
