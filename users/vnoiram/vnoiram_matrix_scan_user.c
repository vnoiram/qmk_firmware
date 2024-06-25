#include "quantum.h"
#include "action.h"
#include "vnoiram_layer_enum.h"
#ifdef TO_KEY_ENABLE
#include "vnoiram_to_key.h"
#endif
#ifdef ALT_TAB_ENABLE
#include "vnoiram_alt_tab.h"
#endif
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

#ifdef LEADER_ENABLE
#include "vnoiram_leader.h"

LEADER_EXTERNS();
#endif

__attribute__ ((weak))
void matrix_scan_keymap(void) {
}

void matrix_scan_user(void) {

#ifdef LEADER_ENABLE
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // one
    // q -> alt + f4
    SEQ_ONE_KEY(KC_Q) {
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    }
    // F1(q) -> alt + f4
    // SEQ_ONE_KEY(KC_F1) {
    //   SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    // }
    // w -> ctrl + s
    // SEQ_ONE_KEY(KC_W) {
    //   SEND_STRING(SS_LCTL("s"));
    // }

    // two
    // qq -> alt + f4, alt + n ( force quit )
    SEQ_TWO_KEYS(KC_Q, KC_Q) {
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));
      SEND_STRING(SS_LALT("n"));
    }
    // F1F1(qq) -> alt + f4 ( force quit )
    // SEQ_TWO_KEYS(KC_F1, KC_F1) {
    //   SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    //   SEND_STRING(SS_LALT("n"));
    // }
    // ex -> run excel
    SEQ_TWO_KEYS(KC_E, KC_X){
      run_win_command("excel");
    }
    // bu/bx -> run burp
    SEQ_TWO_KEYS(KC_B, KC_U){
      run_win_command("burp");
    }
    // SEQ_TWO_KEYS(KC_B, KC_X){
    //   run_win_command("burp");
    // }
    // ff -> firefox
    SEQ_TWO_KEYS(KC_F, KC_F){
      run_win_r_command("firefox");
    }
    // pp -> run powerpoint
    SEQ_TWO_KEYS(KC_P, KC_P) {
      run_win_command("powerpoint");
    }
    // wo -> run word
    SEQ_TWO_KEYS(KC_W, KC_O) {
      run_win_command("word");
    }

    // three
    SEQ_THREE_KEYS(KC_T, KC_R, KC_S){
      run_win_r_command("shell:recycleBinFolder");
    }

    // four
    SEQ_FOUR_KEYS(KC_N, KC_O, KC_T, KC_E){
      run_win_r_command("notepad");
    }

    // if tap esc -> leave leader (set leading false)
    leader_esc_exit() {
      leading = false;
    }
  }
#endif

#ifdef ALT_TAB_ENABLE
  matrix_scan_user_alt_tab();
#endif

#ifdef TO_KEY_ENABLE
  matrix_scan_user_to_key();
#endif

  matrix_scan_keymap();
}
