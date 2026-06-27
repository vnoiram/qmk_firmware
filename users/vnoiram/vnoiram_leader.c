#ifdef LEADER_ENABLE
#include "quantum.h"
#include "vnoiram_leader.h"

// void _run_win_command(const char str[], const bool full_name, const bool admin, const int t) {
//     if (admin || full_name) {
//         SEND_STRING(SS_LGUI("r"));
//     } else {
//         SEND_STRING(SS_TAP(X_LGUI));
//     }
//     wait_ms(t);
//     send_string(str);
//     if (admin) {
//         SEND_STRING(SS_DOWN(X_LCTL));
//         SEND_STRING(SS_LSFT("\n"));
//         SEND_STRING(SS_UP(X_LCTL));
//     }
//     SEND_STRING("\1\4" STRINGIZE(t));
//     if (admin) {
//         SEND_STRING(SS_TAP(X_LEFT));
//     }
//     SEND_STRING(SS_TAP(X_ENT));
// }

// void run_win_command(const char str[]) {
//     _run_win_command(str, false, false, RUN_WIN_CMD_WAIT);
// }

// void run_win_r_admin_command(const char str[]) {
//     _run_win_command(str, true, true, RUN_WIN_CMD_WAIT);
// }

void run_win_r_command(const char str[]) {
    SEND_STRING(SS_LGUI("r"));
    wait_ms(RUN_WIN_CMD_WAIT);
    send_string(str);
    SEND_STRING(SS_TAP(X_ENT));
}

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    // one
    // q -> alt + f4
    if (leader_sequence_one_key(KC_Q)) {
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));

    // two
    // qq -> alt + f4, alt + n ( force quit )
    } else if (leader_sequence_two_keys(KC_Q, KC_Q)) {
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));
      SEND_STRING(SS_LALT("n"));

    // three
    } else if (leader_sequence_three_keys(KC_T, KC_R, KC_S)) {
      run_win_r_command("shell:recycleBinFolder");

    // four
    } else if (leader_sequence_four_keys(KC_N, KC_O, KC_T, KC_E)) {
      run_win_r_command("notepad");
    }

}
#endif /* LEADER_ENABLE */

/* ---------------------------------------------------------------
 * MINE_LEADER_ENABLE: フラグベース自前 LEADER
 * --------------------------------------------------------------- */
#ifdef MINE_LEADER_ENABLE
#include "quantum.h"
#include "vnoiram_leader.h"
#include "vnoiram_keycodes.h"

#define MINE_LEADER_TIMEOUT 400

static bool     mine_leader_active = false;
static uint16_t mine_leader_seq[4] = {0};
static uint8_t  mine_leader_len    = 0;
static uint16_t mine_leader_timer  = 0;

void run_win_r_command(const char str[]) {
    SEND_STRING(SS_LGUI("r"));
    wait_ms(RUN_WIN_CMD_WAIT);
    send_string(str);
    SEND_STRING(SS_TAP(X_ENT));
}

static void mine_leader_fire(void) {
    uint16_t *s = mine_leader_seq;
    uint8_t   n = mine_leader_len;
    if      (n==1 && s[0]==KC_Q)                                               { SEND_STRING(SS_LALT(SS_TAP(X_F4))); }
    else if (n==2 && s[0]==KC_Q && s[1]==KC_Q)                                 { SEND_STRING(SS_LALT(SS_TAP(X_F4))); SEND_STRING(SS_LALT("n")); }
    else if (n==3 && s[0]==KC_T && s[1]==KC_R && s[2]==KC_S)                   { run_win_r_command("shell:recycleBinFolder"); }
    else if (n==4 && s[0]==KC_N && s[1]==KC_O && s[2]==KC_T && s[3]==KC_E)    { run_win_r_command("notepad"); }
}

static void mine_leader_cancel(void) {
    mine_leader_active = false;
    mine_leader_len    = 0;
}

static bool mine_leader_is_prefix(uint16_t kc) {
    uint8_t   n = mine_leader_len;
    uint16_t *s = mine_leader_seq;
    if (n == 0) return kc==KC_Q || kc==KC_T || kc==KC_N;
    if (s[0]==KC_Q && n==1) return kc==KC_Q;
    if (s[0]==KC_T && n==1) return kc==KC_R;
    if (s[0]==KC_T && n==2) return kc==KC_S;
    if (s[0]==KC_N && n==1) return kc==KC_O;
    if (s[0]==KC_N && n==2) return kc==KC_T;
    if (s[0]==KC_N && n==3) return kc==KC_E;
    return false;
}

bool process_record_user_leader(uint16_t kc, keyrecord_t *r) {
    if (kc == MY_LEADER) {
        if (r->event.pressed) {
            mine_leader_active = true;
            mine_leader_len    = 0;
            mine_leader_timer  = timer_read();
        }
        return false;
    }

    if (!mine_leader_active) return true;
    if (!r->event.pressed)   return false;

    if (!mine_leader_is_prefix(kc)) {
        mine_leader_cancel();
        return false;
    }

    mine_leader_seq[mine_leader_len++] = kc;
    mine_leader_timer = timer_read();

    if (mine_leader_len==2 && mine_leader_seq[0]==KC_Q) { mine_leader_fire(); mine_leader_cancel(); }
    else if (mine_leader_len==3)                         { mine_leader_fire(); mine_leader_cancel(); }
    else if (mine_leader_len==4)                         { mine_leader_fire(); mine_leader_cancel(); }

    return false;
}

void matrix_scan_user_leader(void) {
    if (mine_leader_active && timer_elapsed(mine_leader_timer) > MINE_LEADER_TIMEOUT) {
        mine_leader_fire();
        mine_leader_cancel();
    }
}
#endif /* MINE_LEADER_ENABLE */
