#pragma once
#ifdef AUTO_SHIFT_ENABLE
#include "quantum.h"
#include "action.h"
#endif

#ifdef MINE_AUTO_SHIFT_ENABLE
bool process_record_user_auto_shift(uint16_t keycode, keyrecord_t *record);
#endif
