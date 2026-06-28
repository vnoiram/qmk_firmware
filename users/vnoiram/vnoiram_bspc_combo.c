#include "vnoiram_bspc_combo.h"

// BSPC ホールド: このms後にキーリピート開始
#define BSPC_COMBO_TIMEOUT  50
// 同時押し検出ウィンドウ: パートナーが先に来たとき、このms以内にBSPCが来たらコンボ
// 人間の同時押しは最低でも10ms以上ずれるが、マトリクスの処理順ズレは1ms以内
#define BSPC_COMBO_WINDOW   10

typedef enum {
    BSPC_IDLE,
    BSPC_PENDING,      // BSPC が先に押された、パートナー待ち
    PARTNER_PENDING,   // パートナーが先に押された（抑制中）、BSPC 待ち
    BSPC_REGISTERED,   // BSPC ホールド中（キーリピート）
    BSPC_COMBO,        // コンボ発火済み、BSPC まだ押下中
} bspc_state_t;

static bspc_state_t bspc_state   = BSPC_IDLE;
static uint16_t     bspc_timer   = 0;
static uint16_t     held_partner = 0;    // PARTNER_PENDING 中の抑制キー
static bool         partner_held = false; // パートナーがまだ物理的に押されているか

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
            if (bspc_state == PARTNER_PENDING) {
                // パートナーが先に来ていた → コンボ発火
                uint16_t action = bspc_get_combo(held_partner);
                bool was_held   = partner_held;
                held_partner    = 0;
                bspc_state      = was_held ? BSPC_COMBO : BSPC_IDLE;
                tap_code16(action);
                return false;
            }
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
            if (bspc_state == BSPC_IDLE) {
                // パートナーが先 → 抑制してウィンドウ開始
                bspc_state   = PARTNER_PENDING;
                bspc_timer   = timer_read();
                held_partner = keycode;
                partner_held = true;
                return false;
            }
        } else {
            if (bspc_state == PARTNER_PENDING && held_partner == keycode) {
                partner_held = false; // ウィンドウ内にリリース、まだ BSPC 待ち
                return false;
            }
            if (bspc_state == BSPC_COMBO) {
                return false; // コンボ中のパートナーリリースは消費
            }
        }
    }

    // ---- 無関係キー ----
    if (record->event.pressed) {
        if (bspc_state == BSPC_PENDING) {
            tap_code(KC_BSPC);
            bspc_state = BSPC_IDLE;
        } else if (bspc_state == PARTNER_PENDING) {
            // パートナー抑制中に別キー → パートナーを解放してから通す
            if (partner_held) {
                register_code(held_partner);
            } else {
                tap_code(held_partner);
            }
            held_partner = 0;
            bspc_state   = BSPC_IDLE;
        }
    }

    return true;
}

void bspc_combo_scan(void) {
    if (bspc_state == BSPC_PENDING && timer_elapsed(bspc_timer) > BSPC_COMBO_TIMEOUT) {
        register_code(KC_BSPC);
        bspc_state = BSPC_REGISTERED;
    }
    if (bspc_state == PARTNER_PENDING && timer_elapsed(bspc_timer) > BSPC_COMBO_WINDOW) {
        // ウィンドウ内に BSPC が来なかった → パートナーを通常送出
        if (partner_held) {
            register_code(held_partner);
        } else {
            tap_code(held_partner);
        }
        held_partner = 0;
        bspc_state   = BSPC_IDLE;
    }
}
