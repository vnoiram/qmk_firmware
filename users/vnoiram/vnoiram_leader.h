#pragma once
#include "quantum.h"

#define RUN_WIN_CMD_WAIT 2000
#define leader_esc_exit() if (leader_sequence[0] == (KC_ESC) || leader_sequence[1] == (KC_ESC) || leader_sequence[2] == (KC_ESC) || leader_sequence[3] == (KC_ESC) || leader_sequence[4] == (KC_ESC))
void _run_win_command(const char str[], const bool full_name, const bool admin, const int t);
void run_win_command(const char str[]);
// void run_win_admin_command(const char str[]);
void run_win_r_command(const char str[]);
// void run_win_r_admin_command(const char str[]);
