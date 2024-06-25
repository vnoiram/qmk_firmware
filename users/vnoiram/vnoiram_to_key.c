#include QMK_KEYBOARD_H
#include "vnoiram_keycodes.h"
#include "vnoiram_layer_enum.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif
#include "vnoiram_to_key.h"

bool process_record_user_to_key(uint16_t keycode, keyrecord_t *record){
  switch (keycode) {
    case TO_KEY_TIME:
      if (!(record->event.pressed)) {
#ifdef CONSOLE_ENABLE
        print("to key time: move key and enable\n");
#endif
        layer_on(_DEFAULT_KEY);
        to_key_time_enable = true;
      }
  }
  if (to_key_time_enable) {
#ifdef CONSOLE_ENABLE
      print("to key time: timer update\n");
#endif
    to_key_time_timer = timer_read();
  }
  return true;
}

void matrix_scan_user_to_key(void){
  // TODO enable still key repeat (keep pressed)
  if (to_key_time_enable){
    if ((layer_state_is(_DEFAULT_KEY) && timer_elapsed(to_key_time_timer) > 1750) || (layer_state_is(_DEFAULT_MICE) && !layer_state_is(_DEFAULT_KEY))) {
#ifdef CONSOLE_ENABLE
      print("to key time: in key to false and key off\n");
#endif
      layer_off(_DEFAULT_KEY);
      to_key_time_enable = false;
    }
  }
}
