#include "vnoiram_bspc_combo.h"


typedef enum {
    BSPC_IDLE,
    BSPC_PENDING,     // BSPC 押下中、パートナー待ち
    BSPC_REGISTERED,  // BSPC ホールド中（キーリピート）
    BSPC_COMBO,       // コンボ発火済み、BSPC まだ押下中
} bspc_state_t;

static bspc_state_t bspc_state = BSPC_IDLE;
static uint16_t     bspc_timer = 0;

typedef struct {
    uint16_t partner;
    uint16_t action;
} bspc_combo_entry_t;

static const bspc_combo_entry_t bspc_combos[] = {
#define BSPC_COMBO(p, a) {p, a},
#include "bspc_combo_table.h"
#undef BSPC_COMBO
};

static uint16_t bspc_get_combo(uint16_t kc) {
    for (uint8_t i = 0; i < ARRAY_SIZE(bspc_combos); i++) {
        if (bspc_combos[i].partner == kc)
            return bspc_combos[i].action;
    }
    return 0;
}

bool process_record_user_bspc_combo(uint16_t keycode, keyrecord_t *record) {
    uint16_t combo_action = bspc_get_combo(keycode);

    // ---- BSPC ----
    if (keycode == KC_BSPC) {
        if (record->event.pressed) {
            bspc_state = BSPC_PENDING;
            bspc_timer = timer_read();
        } else {
            if      (bspc_state == BSPC_PENDING)    tap_code(KC_BSPC);
            else if (bspc_state == BSPC_REGISTERED) unregister_code(KC_BSPC);
            bspc_state = BSPC_IDLE;
        }
        return false;
    }

    // ---- パートナーキー ----
    if (combo_action) {
        if (record->event.pressed) {
            if (bspc_state == BSPC_PENDING || bspc_state == BSPC_COMBO) {
                // BSPC が先に押されていた → コンボ発火
                bspc_state = BSPC_COMBO;
                tap_code16(combo_action);
                return false;
            }
        } else {
            if (bspc_state == BSPC_COMBO) {
                return false;  // コンボ中のパートナーリリースは消費
            }
        }
    }

    // ---- 無関係キー ----
    if (record->event.pressed && bspc_state == BSPC_PENDING) {
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
