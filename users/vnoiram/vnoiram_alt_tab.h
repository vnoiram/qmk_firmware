#pragma once
#include QMK_KEYBOARD_H
#include "vnoiram_keycodes.h"
#include "vnoiram_layer_enum.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

#ifdef ALT_TAB_ENABLE
bool is_alt_tab_active;
#endif
uint16_t my_alt_tab_timer;

bool process_record_user_alt_tab(uint16_t keycode, keyrecord_t *record);
void matrix_scan_user_alt_tab(void);
