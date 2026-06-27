#pragma once
#include "lib/keyball/keyball.h"

enum custom_keycodes {
  // CTRL_J = KEYBALL_SAFE_RANGE,
  // MY_SPACE,
  // MY_RESET,
#if defined(ALT_TAB_ENABLE) || defined(ALT_TAB_BY_LAYER_ENABLE)
  MY_ALT_TAB = KEYBALL_SAFE_RANGE,
#ifdef JTU_ENABLE
  JTU_TOGGLE,
#endif
#ifdef TO_KEY_ENABLE
  TO_KEY_TIME,
#endif
#else
  // ALT_TAB disabled
  // ALT_TAB_LEFT,
  // ALT_TAB_UP,
  // ALT_TAB_DOWN,
  // ALT_TAB_RGHT,
  // ALT_TAB_ENT,
  // ALT_TAB_ESC,
#ifdef JTU_ENABLE
  JTU_TOGGLE = KEYBALL_SAFE_RANGE,
#ifdef TO_KEY_ENABLE
  TO_KEY_TIME,
#endif
#else
#ifdef TO_KEY_ENABLE
  TO_KEY_TIME = KEYBALL_SAFE_RANGE,
#endif
#endif
#endif
#ifdef MINE_LEADER_ENABLE
  MY_LEADER,
#endif
  VNOIRAM_SAFE_RANGE,
};
