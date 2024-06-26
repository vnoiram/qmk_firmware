#ifdef LEADER_ENABLE
#include "quantum.h"
#include "vnoiram_leader.h"

// void run_win_r_command(const char str[])) {
//     SEND_STRING(SS_LGUI("r"));
//     SEND_STRING(SS_DELAY(640));
//     send_string(str);
//     SEND_STRING(SS_TAP(X_ENT));
// }
//
// void run_win_r_with_admin_command(const char str[])) {
//     SEND_STRING(SS_LGUI("r"));
//     SEND_STRING(SS_DELAY(640));
//     send_string(str);
//     SEND_STRING(SS_DOWN(X_LCTL));
//     SEND_STRING(SS_LSFT("\n"));
//     SEND_STRING(SS_UP(X_LCTL));
//     SEND_STRING(SS_DELAY(800));
//     SEND_STRING(SS_TAP(X_LEFT));
//     SEND_STRING(SS_TAP(X_ENT));
// }
//
// void run_win_command(const char str[])) {
//     SEND_STRING(SS_TAP(X_LGUI));
//     SEND_STRING(SS_DELAY(640));
//     send_string(str);
//     SEND_STRING(SS_DELAY(640));
//     SEND_STRING(SS_TAP(X_ENT));
// }
//

void _run_win_command(const char str[], const bool full_name, const bool admin, const int t) {
    if (admin || full_name) {
        SEND_STRING(SS_LGUI("r"));
    } else {
        SEND_STRING(SS_TAP(X_LGUI));
    }
    // SEND_STRING("\1\4" STRINGIZE(t));
    wait_ms(t);
    send_string(str);
    if (admin) {
        SEND_STRING(SS_DOWN(X_LCTL));
        SEND_STRING(SS_LSFT("\n"));
        SEND_STRING(SS_UP(X_LCTL));
    }
    SEND_STRING("\1\4" STRINGIZE(t));
    if (admin) {
        SEND_STRING(SS_TAP(X_LEFT));
    }
    SEND_STRING(SS_TAP(X_ENT));
}

void run_win_command(const char str[]) {
    _run_win_command(str, false, false, RUN_WIN_CMD_WAIT);
}

// void run_win_admin_command(const char str[])) {
//     _run_win_command(str, false, true, RUN_WIN_CMD_WAIT);
// }

void run_win_r_command(const char str[]) {
    _run_win_command(str, true, false, RUN_WIN_CMD_WAIT);
}

// void run_win_r_admin_command(const char str[])) {
//     _run_win_command(str, true, true, RUN_WIN_CMD_WAIT);
// }


void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    // one
    // q -> alt + f4
    if (leader_sequence_one_key(KC_Q)) {
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    // F1(q) -> alt + f4
    // } else if (leader_sequence_one_key(KC_F1)) {
    //   SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    // }
    // w -> ctrl + s
    // } else if (leader_sequence_one_key(KC_W)) {
    //   SEND_STRING(SS_LCTL("s"));
    // }

    // two
    // qq -> alt + f4, alt + n ( force quit )
    } else if (leader_sequence_two_keys(KC_Q, KC_Q)) {
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));
      SEND_STRING(SS_LALT("n"));
    // }
    // F1F1(qq) -> alt + f4 ( force quit )
    // } else if (leader_sequence_two_keys(KC_F1, KC_F1) {
    //   SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    //   SEND_STRING(SS_LALT("n"));
    // }
    // ex -> run excel
    // } else if (leader_sequence_two_keys(KC_E, KC_X)) {
    //   run_win_command("excel");
    // }
    // bu/bx -> run burp
    // } else if (leader_sequence_two_keys(KC_B, KC_U)) {
    //   run_win_command("burp");
    // }
    // // } else if (leader_sequence_two_keys(KC_B, KC_X)) {
    // //   run_win_command("burp");
    // // }
    // // ff -> firefox
    // } else if (leader_sequence_two_keys(KC_F, KC_F)) {
    //   run_win_r_command("firefox");
    // }
    // // pp -> run powerpoint
    // } else if (leader_sequence_two_keys(KC_P, KC_P)) {
    //   run_win_command("powerpoint");
    // }
    // // wo -> run word
    // } else if (leader_sequence_two_keys(KC_W, KC_O)) {
    //   run_win_command("word");
    // }

    // three
    } else if (leader_sequence_three_keys(KC_T, KC_R, KC_S)) {
      run_win_r_command("shell:recycleBinFolder");
    // }

    // four
    } else if (leader_sequence_four_keys(KC_N, KC_O, KC_T, KC_E)) {
      run_win_r_command("notepad");
    }

}
#endif
