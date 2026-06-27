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
#endif
