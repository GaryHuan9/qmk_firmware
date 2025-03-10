//License Header

#include "keymap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
    [DEFAULT] = LAYOUT_91_ansi(
        KC_MPLY,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_PSCR,  KC_DEL,   LK_SCRN,
        TO(L_G),  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,            KC_PGUP,
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,            KC_PGDN,
        _______,  MT_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     MT_SCLN,  KC_QUOT,             KC_ENT,             KC_HOME,
        _______,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,             KC_RSFT,  KC_UP,
        _______,  KC_LCTL,  KC_LGUI,  KC_LALT,  OSL(L_O),           KC_SPC,                        KC_SPC,             OSL(L_O), KC_RALT,   KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [OVERLAY] = LAYOUT_91_ansi(
        KC_MUTE,  RM_TOGG,  KC_BRID,  KC_BRIU,  KC_MAIL,  KC_MYCM,  RM_VALD,   RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,  _______,  KC_PWR,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,  TAB_SWT,  _______,  _______,  _______,  _______,  _______,   KC_9,     KC_0,     KC_MINS,  KC_EQL,   _______,  _______,   _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,             _______,            QK_BOOT,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  KC_LBRC,  KC_RBRC,  _______,  _______,  _______,             _______,  _______,
        QK_BOOT,  _______,  _______,  _______,  _______,            KC_DEL,                        KC_BSPC,            _______,  _______,   _______,  _______,  _______,  _______),

    [GAMING] = LAYOUT_91_ansi(
        KC_MUTE,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  KC_MUTE,
        TO(L_D),  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,  KC_LCTL,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  KC_SCLN,  _______,             _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,
        _______,  _______,  _______,  _______,  KC_NO,              _______,                       _______,            KC_NO,    _______,   _______,  _______,  _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] =
{
    [DEFAULT] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [OVERLAY] = { ENCODER_CCW_CW(MS_WHLL, MS_WHLR), ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB)) },
    [GAMING]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};

#endif

void keyboard_post_init_user(void)
{
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_cool_layer_anim);
    rgb_matrix_set_speed_noeeprom(100);
    rgb_matrix_sethsv_noeeprom(0, 0, 255);
}

bool process_detected_host_os_user(os_variant_t os)
{
    switch (os)
    {
        case OS_WINDOWS:
        {
            layer_move(GAMING);
            break;
        }
        default:
        {
            layer_move(DEFAULT);
            break;
        }
    }

    return true;
}
