# Include my libraries
SRC += vnoiram_matrix_scan_user.c
SRC += vnoiram_process_record_user.c
SRC += vnoiram_tapping_term.c

# ALT_TAB
# option enable and add src
ifeq ($(strip $(ALT_TAB_BY_LAYER_ENABLE)), yes)
  OPT_DEFS += -DALT_TAB_BY_LAYER_ENABLE
	SRC += vnoiram_alt_tab.c
endif
ifeq ($(strip $(ALT_TAB_ENABLE)), yes)
  OPT_DEFS += -DALT_TAB_ENABLE
	SRC += vnoiram_alt_tab.c
endif

# AUTO_SHIFT
ifeq ($(strip $(AUTO_SHIFT_ENABLE)), yes)
  OPT_DEFS += -DAUTO_SHIFT_ENABLE
	SRC += vnoiram_auto_shift.c
endif

# JTU
# option enable and add src
ifeq ($(strip $(JTU_ENABLE)), yes)
  OPT_DEFS += -DJTU_ENABLE
	SRC += jtu_custom_keycodes.c
endif

# leader
ifeq ($(strip $(LEADER_ENABLE)), yes)
  # Include my fancy rgb functions source here
	SRC += vnoiram_leader.c
endif

# ONE_HAND_GAME_ENABLE
ifeq ($(strip $(ONE_HAND_GAME_ENABLE)), yes)
  OPT_DEFS += -DONE_HAND_GAME_ENABLE
	# SRC += vnoiram_one_hand_game.c
endif

# oled
ifeq ($(strip $(OLED_ENABLE)), yes)
  # Include my fancy rgb functions source here
	SRC += vnoiram_oled.c
endif

# POINTING_DEVICE_AUTO_MOUSE_ENABLE
ifeq ($(strip $(POINTING_DEVICE_AUTO_MOUSE_ENABLE)), yes)
  OPT_DEFS += -DPOINTING_DEVICE_AUTO_MOUSE_ENABLE
	SRC += vnoiram_auto_mouse_layer.c
endif

# TAP_DANCE
ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
  # Include my fancy rgb functions source here
	SRC += vnoiram_tapping.c
endif

# TO_KEY
# option enable and add src
ifeq ($(strip $(TO_KEY_ENABLE)), yes)
  OPT_DEFS += -DTO_KEY_ENABLE
	SRC += vnoiram_to_key.c
endif

