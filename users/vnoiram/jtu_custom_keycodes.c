#include QMK_KEYBOARD_H
#include "jtu_custom_keycodes.h"
#include "vnoiram_layer_enum.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

extern bool is_jtu_active;

typedef struct {
    uint16_t us_key;
    uint16_t jp_key;
    uint16_t jp_sft_key;
    bool is_sft_jtu_sft_key;
    bool is_sft_jtu_key;
} jtu_key_map_t;

static const jtu_key_map_t PROGMEM jtu_map[] = {
    { KC_2,    KC_2,    KC_LBRC, false, false },
    { KC_6,    KC_6,    KC_EQL,  false, false },
    { KC_7,    KC_7,    KC_6,    true,  false },
    { KC_8,    KC_8,    KC_QUOT, true,  false },
    { KC_9,    KC_9,    KC_8,    true,  false },
    { KC_0,    KC_0,    KC_9,    true,  false },
    { KC_MINS, KC_MINS, KC_INT1, true,  false },
    { KC_EQL,  KC_MINS, KC_SCLN, true,  true  },
    { KC_LBRC, KC_RBRC, KC_RBRC, true,  false },
    { KC_RBRC, KC_NUHS, KC_NUHS, true,  false },
    { KC_BSLS, KC_INT1, KC_INT3, true,  false },
    { KC_SCLN, KC_SCLN, KC_QUOT, false, false },
    { KC_QUOT, KC_7,    KC_2,    true,  true  },
    { KC_GRV,  KC_LBRC, KC_EQL,  true,  true  },
};

static void tap_jtu_code(keyrecord_t *record, uint16_t jp_key, uint16_t jp_sft_key,
                         bool is_sft_jtu_sft_key, bool is_sft_jtu_key,
                         bool as_sft, bool lshift) {
    if (!record->event.pressed) return;

    if (lshift || as_sft) {
        if (lshift) unregister_code(KC_LSFT);
        if (is_sft_jtu_sft_key) register_code(KC_LSFT);
        register_code(jp_sft_key);
        unregister_code(jp_sft_key);
        if (is_sft_jtu_sft_key) unregister_code(KC_LSFT);
        if (lshift) register_code(KC_LSFT);
#ifdef CONSOLE_ENABLE
        uprintf("jtu: 0x%04X sended\n", jp_sft_key);
#endif
    } else {
        if (is_sft_jtu_key) register_code(KC_LSFT);
        register_code(jp_key);
        unregister_code(jp_key);
        if (is_sft_jtu_key) unregister_code(KC_LSFT);
#ifdef CONSOLE_ENABLE
        uprintf("jtu: 0x%04X sended\n", jp_key);
#endif
    }
}

bool process_record_user_jtu(uint16_t keycode, keyrecord_t *record) {
    if (keycode == JTU_TOGGLE) {
#ifdef CONSOLE_ENABLE
        print("jtu toggle\n");
#endif
        if (record->event.pressed) {
            is_jtu_active = !is_jtu_active;
        }
        return false;
    }

    if (!is_jtu_active) return true;

    bool lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);

    for (uint8_t i = 0; i < sizeof(jtu_map) / sizeof(jtu_map[0]); i++) {
        uint16_t us_key        = pgm_read_word(&jtu_map[i].us_key);
        uint16_t jp_key        = pgm_read_word(&jtu_map[i].jp_key);
        uint16_t jp_sft_key    = pgm_read_word(&jtu_map[i].jp_sft_key);
        bool is_sft_jtu_sft    = pgm_read_byte(&jtu_map[i].is_sft_jtu_sft_key);
        bool is_sft_jtu        = pgm_read_byte(&jtu_map[i].is_sft_jtu_key);

        if (keycode == us_key || keycode == S(us_key)) {
            bool as_sft = (keycode == S(us_key));
            tap_jtu_code(record, jp_key, jp_sft_key, is_sft_jtu_sft, is_sft_jtu, as_sft, lshift);
            return false;
        }
    }

    return true;
}
