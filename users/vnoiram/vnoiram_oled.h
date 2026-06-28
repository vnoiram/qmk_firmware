#pragma once
#include "quantum.h"
#include "jtu_custom_keycodes.h"

extern bool is_jtu_active;

#ifdef MINE_OLED_ENABLE
void mine_oled_init(void);
void mine_oled_render(void);
#endif
