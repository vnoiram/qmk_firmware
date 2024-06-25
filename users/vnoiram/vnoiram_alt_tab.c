#include QMK_KEYBOARD_H
#include "vnoiram_keycodes.h"
#include "vnoiram_layer_enum.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif
#include "vnoiram_alt_tab.h"

// for alt_tab mode
void proc_alt_tab(keyrecord_t *record, uint16_t regist_keycode, bool is_end){
  if (record->event.pressed) {
#ifdef CONSOLE_ENABLE
    print("alttab: tap alt tab\n");
#endif
    tap_code16(regist_keycode);
      // is_alt_tab_active = true;
    if (is_end) {
      unregister_code(KC_LALT);
#if defined(ALT_TAB_ENABLE)
      is_alt_tab_active = false;
#elif defined(ALT_TAB_BY_LAYER_ENABLE)
      layer_off(_ALTTAB);
#endif
    } else {
      my_alt_tab_timer = timer_read();
    }
  }
}

bool process_record_user_alt_tab(uint16_t keycode, keyrecord_t *record){
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    // alt_tab mode
    case MY_ALT_TAB:
      if (record->event.pressed) {
#if defined(ALT_TAB_ENABLE)
        if (!is_alt_tab_active) {
#elif defined(ALT_TAB_BY_LAYER_ENABLE)
        if (!layer_state_is(_ALTTAB)) {
#endif
          register_code(KC_LALT);
#ifdef CONSOLE_ENABLE
          print("alttab: kc lalt\n");
#endif
        } else {
          register_code(KC_TAB);
#ifdef CONSOLE_ENABLE
          print("alttab: kc tab\n");
#endif
        }
        my_alt_tab_timer = timer_read();
      } else {
#if defined(ALT_TAB_ENABLE)
        if (!is_alt_tab_active) {
#elif defined(ALT_TAB_BY_LAYER_ENABLE)
        if (!layer_state_is(_ALTTAB)) {
#endif
          if (timer_elapsed(my_alt_tab_timer) < ALT_TAB_TIMEOUT) {
#ifdef CONSOLE_ENABLE
            print("alttab: alt tab layer is on\n");
#endif
#if defined(ALT_TAB_ENABLE)
            is_alt_tab_active = true;
#elif defined(ALT_TAB_BY_LAYER_ENABLE)
            layer_on(_ALTTAB);
#endif
            tap_code(KC_TAB);
          } else {
            unregister_code(KC_LALT);
          }
        } else {
          unregister_code(KC_TAB);
        }
      }
      return false;
  }

#if defined(ALT_TAB_ENABLE)
  if (is_alt_tab_active) {
#elif defined(ALT_TAB_BY_LAYER_ENABLE)
  if (layer_state_is(_ALTTAB)) {
#endif
    switch (keycode) { // This will do most of the grunt work with the keycodes.#
      case KC_H:
        proc_alt_tab(record, KC_LEFT, false);
        return false;
      case KC_J:
        proc_alt_tab(record, KC_DOWN, false);
        return false;
      case KC_K:
        proc_alt_tab(record, KC_UP, false);
        return false;
      case KC_L:
        proc_alt_tab(record, KC_RGHT, false);
        return false;
      case KC_ENT:
      case LT(_RNUM,KC_ENT):
        proc_alt_tab(record, KC_ENT, true);
        return false;
      case KC_ESC:
      default:
        proc_alt_tab(record, KC_ESC, true);
        return false;
      // alt_tab mode
    }
  }

  return true;
}

void matrix_scan_user_alt_tab(void){
#if defined(ALT_TAB_ENABLE)
  if (is_alt_tab_active) {
#elif defined(ALT_TAB_BY_LAYER_ENABLE)
  if (layer_state_is(_ALTTAB)) {
#endif
    if (timer_elapsed(my_alt_tab_timer) > 1000) {
#ifdef CONSOLE_ENABLE
      print("alttab: disable alt_tab\n");
#endif
      unregister_code(KC_LALT);
#if defined(ALT_TAB_ENABLE)
      is_alt_tab_active = false;
#elif defined(ALT_TAB_BY_LAYER_ENABLE)
      layer_off(_ALTTAB);
#endif
    }
  }
}
