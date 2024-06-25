#include "quantum.h"
#include "action.h"
#include "vnoiram_process_record_user.h"
#ifdef TO_KEY_ENABLE
#include "vnoiram_to_key.h"
#endif
#ifdef ALT_TAB_ENABLE
#include "vnoiram_alt_tab.h"
#endif
#ifdef JTU_ENABLE
#include "jtu_custom_keycodes.h"
#endif
#include "vnoiram_layer_enum.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

// process_record_user
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

// need first!!
#ifdef TO_KEY_ENABLE
  if (process_record_user_to_key(keycode, record) == false){
    return false;
  }
#endif

#ifdef ALT_TAB_ENABLE
  if (process_record_user_alt_tab(keycode, record) == false){
    return false;
  }
#endif

#ifdef JTU_ENABLE
  if (process_record_user_jtu(keycode, record) == false) {
    return false;
  }
#endif

  return process_record_keymap(keycode, record);
}
