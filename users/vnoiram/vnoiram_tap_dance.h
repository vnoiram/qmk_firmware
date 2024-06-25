#pragma once
#ifdef TAP_DANCE_ENABLE
// tap dance
enum {
  TD_LBRC,
  TD_RBRC,
  TD_RESET
};
void dance_td_reset(qk_tap_dance_state_t *state, void *user_data);

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
    [TD_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),
    [TD_RESET] = ACTION_TAP_DANCE_FN(dance_td_reset)
};

void dance_td_reset(qk_tap_dance_state_t *state, void *user_data){
  if (state->count >= 2) {
    reset_keyboard();
  }
}

#endif
