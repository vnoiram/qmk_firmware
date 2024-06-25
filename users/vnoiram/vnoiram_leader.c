#include "quantum.h"
#include "vnoiram_leader.h"

// void run_win_r_command(const char str[]){
//     SEND_STRING(SS_LGUI("r"));
//     SEND_STRING(SS_DELAY(640));
//     send_string(str);
//     SEND_STRING(SS_TAP(X_ENT));
// }
//
// void run_win_r_with_admin_command(const char str[]){
//     SEND_STRING(SS_LGUI("r"));
//     SEND_STRING(SS_DELAY(640));
//     send_string(str);
//     SEND_STRING(SS_DOWN(X_LCTRL));
//     SEND_STRING(SS_LSFT("\n"));
//     SEND_STRING(SS_UP(X_LCTRL));
//     SEND_STRING(SS_DELAY(800));
//     SEND_STRING(SS_TAP(X_LEFT));
//     SEND_STRING(SS_TAP(X_ENT));
// }
//
// void run_win_command(const char str[]){
//     SEND_STRING(SS_TAP(X_LGUI));
//     SEND_STRING(SS_DELAY(640));
//     send_string(str);
//     SEND_STRING(SS_DELAY(640));
//     SEND_STRING(SS_TAP(X_ENT));
// }
//

void _run_win_command(const char str[], const bool full_name, const bool admin, const int t){
    if (admin || full_name) {
        SEND_STRING(SS_LGUI("r"));
    } else {
        SEND_STRING(SS_TAP(X_LGUI));
    }
    // SEND_STRING("\1\4" STRINGIZE(t));
    wait_ms(t);
    send_string(str);
    if (admin) {
        SEND_STRING(SS_DOWN(X_LCTRL));
        SEND_STRING(SS_LSFT("\n"));
        SEND_STRING(SS_UP(X_LCTRL));
    }
    SEND_STRING("\1\4" STRINGIZE(t));
    if (admin) {
        SEND_STRING(SS_TAP(X_LEFT));
    }
    SEND_STRING(SS_TAP(X_ENT));
}

void run_win_command(const char str[]){
    _run_win_command(str, false, false, RUN_WIN_CMD_WAIT);
}

// void run_win_admin_command(const char str[]){
//     _run_win_command(str, false, true, RUN_WIN_CMD_WAIT);
// }

void run_win_r_command(const char str[]){
    _run_win_command(str, true, false, RUN_WIN_CMD_WAIT);
}

// void run_win_r_admin_command(const char str[]){
//     _run_win_command(str, true, true, RUN_WIN_CMD_WAIT);
// }

