#pragma once
#include QMK_KEYBOARD_H
#include "vnoiram_keycodes.h"
#include "vnoiram_layer_enum.h"
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

uint16_t to_key_time_timer;
bool to_key_time_enable;

bool process_record_user_to_key(uint16_t keycode, keyrecord_t *record);
void matrix_scan_user_to_key(void);
