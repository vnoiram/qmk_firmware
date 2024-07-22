#include QMK_KEYBOARD_H
#include "jtu_custom_keycodes.h"
#include "vnoiram_layer_enum.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

extern bool is_jtu_active;
static bool as_sft = false;

// jtu_sft_key -> shiftの時の
// jtu_key -> defoの時の
// is_sft_jtu_sft_key -> shiftの時のキーがsftかどうか
// is_sft_jtu_key -> defoの時のキーがsftかどうか
// as_sft -> sftがONじゃなくてもsftとしてfireするかどうか
// void tap_jtu_code(uint16_t keycode, keyrecord_t *record, uint16_t jtu_sft_key, uint16_t jtu_key, bool is_sft_jtu_sft_key, bool is_sft_jtu_key, bool as_sft, bool lshift, bool rshift) {
void tap_jtu_code(uint16_t keycode, keyrecord_t *record, uint16_t jtu_sft_key, uint16_t jtu_key, bool is_sft_jtu_sft_key, bool is_sft_jtu_key, bool as_sft, bool lshift) {
  if (record->event.pressed) {
    // if (lshift || rshift || as_sft) {
    if (lshift || as_sft) {
      if (lshift) unregister_code(KC_LSFT);
      // if (rshift) unregister_code(KC_RSFT);
      if (is_sft_jtu_sft_key) register_code(KC_LSFT);
      register_code(jtu_sft_key);
      unregister_code(jtu_sft_key);
      if (is_sft_jtu_sft_key) unregister_code(KC_LSFT);
      if (lshift) register_code(KC_LSFT);
      // if (rshift) register_code(KC_RSFT);
#ifdef CONSOLE_ENABLE
      uprintf("jtu ju 0x%04X sended\n", jtu_sft_key);
#endif
    } else {
      if (is_sft_jtu_key) register_code(KC_LSFT);
      register_code(jtu_key);
      unregister_code(jtu_key);
#ifdef CONSOLE_ENABLE
      uprintf("jtu ju 0x%04X sended\n", jtu_key);
#endif
      if (is_sft_jtu_key) unregister_code(KC_LSFT);
    }
  }
}

bool process_record_user_jtu(uint16_t keycode, keyrecord_t *record) {
  static bool lshift = false;
  // static bool rshift = false;
  as_sft = false;

  switch (keycode) {
    case JTU_TOGGLE:
#ifdef CONSOLE_ENABLE
      print("jtu toggle\n");
#endif
      if (record->event.pressed) {
        is_jtu_active = !is_jtu_active;
      }
      break;
  }

  if (is_jtu_active) {
    lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
    // rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);

    switch (keycode) {
      case S(KC_2):
        as_sft = true;
      case KC_2:
        tap_jtu_code(keycode, record, KC_LBRC, KC_2, false, false, (false || as_sft), lshift);
        // tap_jtu_code(keycode, record, KC_LBRC, KC_2, false, false, (false || as_sft), lshift, rshift);
        return false;
      case S(KC_6):
        as_sft = true;
      case KC_6:
        tap_jtu_code(keycode, record, KC_EQL, KC_6, false, false, (false || as_sft), lshift);
        return false;
      case S(KC_7):
        as_sft = true;
      case KC_7:
        tap_jtu_code(keycode, record, KC_6, KC_7, true, false, (false || as_sft), lshift);
        return false;
      case S(KC_8):
        as_sft = true;
      case KC_8:
        tap_jtu_code(keycode, record, KC_QUOT, KC_8, true, false, (false || as_sft), lshift);
        return false;
      case S(KC_9):
        as_sft = true;
      case KC_9:
        tap_jtu_code(keycode, record, KC_8, KC_9, true, false, (false || as_sft), lshift);
        return false;
      case S(KC_0):
        as_sft = true;
      case KC_0:
        tap_jtu_code(keycode, record, KC_9, KC_0, true, false, (false || as_sft), lshift);
        return false;
      case S(KC_MINS):
        as_sft = true;
      case KC_MINS:
        tap_jtu_code(keycode, record, KC_INT1, KC_MINS, true, false, (false || as_sft), lshift);
        return false;
      case S(KC_EQL):
        as_sft = true;
      case KC_EQL:
        tap_jtu_code(keycode, record, KC_SCLN, KC_MINS, true, true, (false || as_sft), lshift);
        return false;
      case S(KC_LBRC):
        as_sft = true;
      case KC_LBRC:
        tap_jtu_code(keycode, record, KC_RBRC, KC_RBRC, true, false, (false || as_sft), lshift);
        return false;
      case S(KC_RBRC):
        as_sft = true;
      case KC_RBRC:
        tap_jtu_code(keycode, record, KC_NUHS, KC_NUHS, true, false, (false || as_sft), lshift);
        return false;
      case S(KC_BSLS):
        as_sft = true;
      case KC_BSLS:
        tap_jtu_code(keycode, record, KC_INT3, KC_INT1, true, false, (false || as_sft), lshift);
        return false;
      case S(KC_SCLN):
        as_sft = true;
      case KC_SCLN:
        tap_jtu_code(keycode, record, KC_QUOT, KC_SCLN, false, false, (false || as_sft), lshift);
        return false;
      case S(KC_QUOT):
        as_sft = true;
      case KC_QUOT:
        tap_jtu_code(keycode, record, KC_2, KC_7, true, true, (false || as_sft), lshift);
        return false;
      case S(KC_GRV):
        as_sft = true;
      case KC_GRV:
        tap_jtu_code(keycode, record, KC_EQL, KC_LBRC, true, true, (false || as_sft), lshift);
        return false;
    }
  }
  return true;
}
