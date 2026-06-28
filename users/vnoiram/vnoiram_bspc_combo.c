#include "vnoiram_bspc_combo.h"

#define BSPC_COMBO_TIMEOUT 50

typedef enum {
    BSPC_IDLE,
    BSPC_PENDING,
    BSPC_REGISTERED,
    BSPC_COMBO,
} bspc_state_t;

static bspc_state_t bspc_state = BSPC_IDLE;
static uint16_t     bspc_timer;

typedef struct {
    uint16_t partner;
    uint16_t action;
} bspc_combo_entry_t;

// PROGMEM を外して RAM に置く（20 bytes）→ pgm_read_word 不要
static const bspc_combo_entry_t bspc_combos[] = {
#define BSPC_COMBO(p, a) {p, a},
#include "bspc_combo_table.h"
#undef BSPC_COMBO
};

static uint16_t bspc_get_combo(uint16_t kc) {
    for (uint8_t i = 0; i < ARRAY_SIZE(bspc_combos); i++) {
        if (bspc_combos[i].partner == kc) {
            return bspc_combos[i].action;
        }
    }
    return 0;
}

bool process_record_user_bspc_combo(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_BSPC) {
        if (record->event.pressed) {
            bspc_state = BSPC_PENDING;
            bspc_timer = timer_read();
        } else {
            if (bspc_state == BSPC_PENDING) {
                tap_code(KC_BSPC);
            } else if (bspc_state == BSPC_REGISTERED) {
                unregister_code(KC_BSPC);
            }
            bspc_state = BSPC_IDLE;
        }
        return false;
    }

    if (record->event.pressed && (bspc_state == BSPC_PENDING || bspc_state == BSPC_COMBO)) {
        uint16_t action = bspc_get_combo(keycode);
        if (action) {
            bspc_state = BSPC_COMBO;
            tap_code16(action);
            return false;
        }
    }

    // PENDING中に無関係キー → BSPCを先に送出してから通す
    if (bspc_state == BSPC_PENDING && record->event.pressed) {
        tap_code(KC_BSPC);
        bspc_state = BSPC_IDLE;
    }

    return true;
}

void bspc_combo_scan(void) {
    if (bspc_state == BSPC_PENDING && timer_elapsed(bspc_timer) > BSPC_COMBO_TIMEOUT) {
        register_code(KC_BSPC);
        bspc_state = BSPC_REGISTERED;
    }
}
