#ifdef OLED_ENABLE
#include "quantum.h"
#include "lib/oledkit/oledkit.h"

#if defined(MASTER_RIGHT)
/* ---------------------------------------------------------------
 * USB 右接続: 左 (non-master) OLED を消灯
 *   - oledkit_render_logo_user を空にして LTO でロゴ描画コードを除去
 *   - 右 (master) はカスタム情報表示を継続
 * --------------------------------------------------------------- */
#include <string.h>
#include "lib/keyball/keyball.h"
#include "vnoiram_oled.h"
#include "jtu_custom_keycodes.h"

/* 左側ロゴ描画を空に override → LTO でロゴフォント描画コードが落ちる */
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
    oled_write_P(PSTR("State: "), false);
    if (is_jtu_active) {
        oled_write("JTU        ", false);
    } else {
        oled_write("NORMAL     ", false);
    }
    keyball_oled_render_ballinfo();
}

#elif defined(MASTER_LEFT)
/* ---------------------------------------------------------------
 * USB 左接続: 右 (non-master) OLED を消灯
 *   - oledkit_render_logo_user を空にして LTO でロゴ描画コードを除去
 *   - 左 (master) はカスタム情報表示を継続
 * --------------------------------------------------------------- */
#include <string.h>
#include "lib/keyball/keyball.h"
#include "vnoiram_oled.h"
#include "jtu_custom_keycodes.h"

/* 右側ロゴ描画を空に override */
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
    oled_write_P(PSTR("State: "), false);
    if (is_jtu_active) {
        oled_write("JTU        ", false);
    } else {
        oled_write("NORMAL     ", false);
    }
    keyball_oled_render_ballinfo();
}

#else
/* ---------------------------------------------------------------
 * MASTER 未定義: 従来どおり両側 OLED を使用
 * --------------------------------------------------------------- */
#include <string.h>
#include "lib/keyball/keyball.h"
#include "vnoiram_oled.h"
#include "jtu_custom_keycodes.h"
#include "vnoiram_layer_enum.h"

void oledkit_render_info_user(void) {
    oled_write_P(PSTR("State: "), false);
    if (is_jtu_active) {
        oled_write("JTU        ", false);
    } else {
#ifdef ONE_HAND_GAME_ENABLE
        if (get_highest_layer(layer_state) == _ONE_HAND_GAME) {
            oled_write("ONEHANDGAME", false);
        } else {
            oled_write("NORMAL     ", false);
        }
#else
        oled_write("NORMAL     ", false);
#endif
    }
    keyball_oled_render_ballinfo();
}

#endif /* MASTER_RIGHT / MASTER_LEFT / else */

#endif /* OLED_ENABLE */
