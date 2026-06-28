#include "quantum.h"
#include "action.h"
#include "vnoiram_layer_enum.h"
#ifdef TO_KEY_ENABLE
#include "vnoiram_to_key.h"
#endif
#if defined(ALT_TAB_ENABLE) || defined(ALT_TAB_BY_LAYER_ENABLE)
#include "vnoiram_alt_tab.h"
#endif
#ifdef MINE_LEADER_ENABLE
#include "vnoiram_leader.h"
#endif
#ifdef BSPC_COMBO_ENABLE
#include "vnoiram_bspc_combo.h"
#endif
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

__attribute__ ((weak))
void matrix_scan_keymap(void) {
}

void matrix_scan_user(void) {

#if defined(ALT_TAB_ENABLE) || defined(ALT_TAB_BY_LAYER_ENABLE)
  matrix_scan_user_alt_tab();
#endif

#ifdef TO_KEY_ENABLE
  matrix_scan_user_to_key();
#endif

#ifdef MINE_LEADER_ENABLE
  matrix_scan_user_leader();
#endif

#ifdef BSPC_COMBO_ENABLE
  bspc_combo_scan();
#endif

  matrix_scan_keymap();
}
