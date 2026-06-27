#ifdef OLED_ENABLE
#include "quantum.h"
#include "lib/oledkit/oledkit.h"

#ifdef LEFT_OLED_DISABLE

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        oled_off();
        return false;
    }
    oledkit_render_info_user();
    return true;
}

#else /* !LEFT_OLED_DISABLE */

#include <string.h>
#include "lib/keyball/keyball.h"
#include "vnoiram_layer_enum.h"
#include "vnoiram_oled.h"
#include "jtu_custom_keycodes.h"

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
//       case _ALTTAB:
//         oled_write(format_14c("ALTTAB"),false);
//         break;
//       default:
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

void oledkit_render_info_user(void) {
  keyball_oled_render_main_state_info();
  keyball_oled_render_ballinfo();
}

#endif /* LEFT_OLED_DISABLE */

#endif /* OLED_ENABLE */
