const key_override_t win_left_override = ko_make_basic( MOD_MASK_CTRL, LALT(KC_LEFT), LGUI(KC_LEFT));
const key_override_t win_right_override = ko_make_basic( MOD_MASK_CTRL, LALT(KC_RGHT), LGUI(KC_RGHT));
const key_override_t win_up_override = ko_make_basic( MOD_MASK_CTRL, LALT(KC_UP), LGUI(KC_UP));
const key_override_t win_down_override = ko_make_basic( MOD_MASK_CTRL, LALT(KC_DOWN), LGUI(KC_DOWN));
const key_override_t brght_up_override = ko_make_basic( MOD_MASK_CTRL, KC_VOLU, KC_BRIU);
const key_override_t brght_down_override = ko_make_basic( MOD_MASK_CTRL,KC_VOLD, KC_BRID);

// JP -> US
// layer memo
// _JP_DEFAULT_MICE, // default jp map
// _JP_DEFAULT_KEY,
// _JP_SFT,
// _JP_SPCL,
// _JP_SCRL,
// _JP_ALTMOVE,
// _JP_RNUM,
// sample
// const jp_to_us__override = ko_make_with_layers(MOD_MASK_SHIFT, KCXXXX, KCXXXX, (1 << _JP_SFT));
// const jp_to_us_KC_2_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LBRC, (1 << _JP_RNUM));
// const jp_to_us_KC_6_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_EQL, (1 << _JP_RNUM));
// const jp_to_us_KC_7_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_6, (1 << _JP_RNUM));
// const jp_to_us_KC_8_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUOT, (1 << _JP_RNUM));
// const jp_to_us_KC_9_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_8, (1 << _JP_RNUM));
// const jp_to_us_KC_0_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_9, KC_0);
// const jp_to_us_KC_MINS_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_INT1, (1 << _JP_RNUM));
// const jp_to_us_KC_EQL_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_SCLN, KC_MINS);
// const jp_to_us_KC_EQL_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_SCLN, KC_MINS);
// const jp_to_us_KC_LBRC_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_RBRC, KC_RBRC);
// const jp_to_us_KC_RBRC_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_NUHS, KC_NUHS);
// const jp_to_us_KC_BSLS_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_INT3, KC_INT1);
// const jp_to_us_KC_SCLN_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUOT, KC_SCLN);
// const jp_to_us_KC_QUOT_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_2, KC_7);
// const jp_to_us_KC_GRV_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_EQL, KC_LBRC);
// const jp_to_us_KC_CAPS_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_CAPS, KC_CAPS);
// const jp_to_us_KC_TILD_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_EQL, KC_EQL);
// const jp_to_us_KC_AT_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LBLC, KC_LBLC);
// const jp_to_us_KC_CIRC_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_EQL, KC_EQL);
// const jp_to_us_KC_AMPR_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_6, KC_6);
// const jp_to_us_KC_ASTR_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUOT, KC_QUOT);
// const jp_to_us_KC_LPRN_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_8, KC_8);
// const jp_to_us_KC_RPRN_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_9, KC_9);
// const jp_to_us_KC_UNDS_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_INT1, KC_INT1);
// const jp_to_us_KC_PLUS_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_SCLN, KC_SCLN);
// const jp_to_us_KC_LCBR_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_RBRC, KC_RBRC);
// const jp_to_us_KC_RCBR_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_NUHS, KC_NUHS);
// const jp_to_us_KC_PIPE_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_INT3, KC_INT3);
// const jp_to_us_KC_COLN_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUOT, KC_QUOT);
// const jp_to_us_KC_DQUO_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_2, KC_2);
// const jp_to_us_KC_PEQL_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_MINS, KC_MINS);
// const jp_to_us_KC_PCMM_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, KC_COMM);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &win_left_override,
    &win_right_override,
    &win_up_override,
    &win_down_override,
    &brght_up_override,
    &brght_down_override,
    NULL
};
