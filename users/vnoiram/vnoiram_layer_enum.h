#pragma once
enum {
#ifdef TO_KEY_ENABLE
  _DEFAULT_MICE = 0, // default map is this
  _DEFAULT_KEY,
#else
  _DEFAULT_KEY = 0, // default map is this
  _DEFAULT_MICE,
#endif
#ifdef ONE_HAND_GAME_ENABLE
  _ONE_HAND_GAME,
#endif
  _SFT,
  _SPCL,
  _SCRL,
  _ALTMOVE,
  _RNUM,
#ifdef ALT_TAB_BY_LAYER_ENABLE
  _ALTTAB,
#endif
  _SPCL_AND_RNUM
};
