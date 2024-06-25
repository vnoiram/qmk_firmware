#ifdef OLED_ENABLE
#include <string.h>
#include "quantum.h"
#include "lib/oledkit/oledkit.h"
#include "lib/keyball/keyball.h"
#include "vnoiram_layer_enum.h"
#include "vnoiram_oled.h"
#include "jtu_custom_keycodes.h"

// __attribute__ ((weak))
// void oledkit_render_info_user(void) {
// }

// static const char *format_14c(const char *c) {
//   static char buf[14] = {0}; // max width 15
//   int l = 14 - strlen(c);
//   for ( int i = 0; i < l; ++i ) {
//     buf[i] = ' ';
//   }
//   int j = 0;
//   for ( int i = l; i < 14; ++i ) {
//     buf[i] = c[j];
//     ++j;
//   }
//   return buf;
// }

// static const char *format_12c(const char *c) {
//   static char buf[12] = {0}; // max width 15
//   int l = 12 - strlen(c);
//   for ( int i = 0; i < l; ++i ) {
//     buf[i] = ' ';
//   }
//   int j = 0;
//   for ( int i = l; i < 12; ++i ) {
//     buf[i] = c[j];
//     ++j;
//   }
//   return buf;
// }

// void keyball_oled_render_layerinfo(void){
//     // Host Keyboard Layer Status
//     oled_write_P(PSTR("Layer: "), false);
//
//     switch (get_highest_layer(layer_state)) {
//       case _DEFAULT_MICE:
//         oled_write(format_14c("DEFAULT_MICE"),false);
//         break;
//       case _DEFAULT_KEY:
//         oled_write(format_14c("DEFAULT_KEY"),false);
//         break;
//       case _SFT:
//         oled_write(format_14c("SFT"),false);
//         break;
//       case _SPCL:
//         oled_write(format_14c("SPCL"),false);
//         break;
//       case _SCRL:
//         oled_write(format_14c("SCRL"),false);
//         break;
//       case _RNUM:
//         oled_write(format_14c("RNUM"),false);
//         break;
//       case _ALTMOVE:
//         oled_write(format_14c("ALTMOVE"),false);
//         break;
//       case _JP_DEFAULT_MICE:
//         oled_write(format_14c("J:DEFAULT_MICE"),false);
//         break;
//       case _JP_DEFAULT_KEY:
//         oled_write(format_14c("J:DEFAULT_KEY"),false);
//         break;
//       case _JP_SFT:
//         oled_write(format_14c("J:SFT"),false);
//         break;
//       case _JP_SPCL:
//         oled_write(format_14c("J:SPCL"),false);
//         break;
//       case _JP_SCRL:
//         oled_write(format_14c("J:SCRL"),false);
//         break;
//       case _JP_RNUM:
//         oled_write(format_14c("J:RNUM"),false);
//         break;
//       case _JP_ALTMOVE:
//         oled_write(format_14c("J:ALTMOVE"),false);
//         break;
//       case _ALTTAB:
//         oled_write(format_14c("ALTTAB"),false);
//         break;
//       default:
//         // Or use the write_ln shortcut over adding '' to the end of your string
//         oled_write(format_14c("Undefined"), false);
//     }
// }

void keyball_oled_render_main_state_info(void){
  // Host Keyboard Layer Status
  oled_write_P(PSTR("State: "), false);

  if (is_jtu_active) {
    oled_write("JTU        ",false);
  } else {
#ifdef ONE_HAND_GAME_ENABLE
    if (get_highest_layer(layer_state) == _ONE_HAND_GAME) {
      oled_write("ONEHANDGAME",false);
    } else {
      oled_write("NORMAL     ",false);
    }
#else
    oled_write("NORMAL     ",false);
#endif
  }
}

// void keyball_oled_render_jpmodeinfo(void){
//   oled_write_P(PSTR("MODE: "), false);
//
//   if (is_jtu_active) {
//     oled_write("     ENABLED",false);
//   } else {
//     oled_write("    DISABLED",false);
//   }
//
// }

void oledkit_render_info_user(void) {
  // keyball_oled_render_layerinfo();
  keyball_oled_render_main_state_info();
  // keyball_oled_render_jpmodeinfo();
  // keyball_oled_render_jpmodeinfo();
  keyball_oled_render_ballinfo();
}
#endif
