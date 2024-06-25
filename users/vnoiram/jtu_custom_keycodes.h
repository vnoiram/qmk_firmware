#pragma once
#include QMK_KEYBOARD_H
#include "vnoiram_keycodes.h"

bool is_jtu_active;

bool process_record_user_jtu(uint16_t keycode, keyrecord_t *record);
