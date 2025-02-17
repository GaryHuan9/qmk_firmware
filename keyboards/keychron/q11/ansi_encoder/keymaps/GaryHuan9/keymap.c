/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers{
    DEFAULT,
    OVERLAY,
    GAMING,
};

#define L_D DEFAULT
#define L_O OVERLAY
#define L_G GAMING

//Mod tap keys
#define MT_CAPS LCTL_T(KC_ESC)
#define MT_SCLN RCTL_T(KC_SCLN)

//One shot keys
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)

//Shortcuts
#define LK_SCRN LGUI(KC_L) //Works in Ubuntu and Windows
#define TAB_SWT LALT(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT_91_ansi(
        KC_MPLY,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_PSCR,  KC_DEL,   LK_SCRN,
        TG(L_G),  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,            KC_PGUP,
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,            KC_PGDN,
        _______,  MT_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     MT_SCLN,  KC_QUOT,             KC_ENT,             KC_HOME,
        _______,  OS_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,             OS_RSFT,  KC_UP,
        _______,  KC_LCTL,  KC_LGUI,  KC_LALT,  OSL(L_O),           KC_SPC,                        KC_SPC,             OSL(L_O), KC_RALT,   KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [OVERLAY] = LAYOUT_91_ansi(
        KC_MUTE,  RM_TOGG,  KC_BRID,  KC_BRIU,  KC_MAIL,  KC_MYCM,  RM_VALD,   RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,  _______,  KC_PWR,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,  TAB_SWT,  _______,  _______,  _______,  _______,  _______,   KC_9,     KC_0,     KC_MINS,  KC_EQL,   _______,  _______,   _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,             _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  KC_LBRC,  KC_RBRC,  _______,  _______,  _______,             _______,  _______,
        QK_BOOT,  _______,  _______,  _______,  _______,            KC_DEL,                        KC_BSPC,            _______,  _______,   _______,  _______,  _______,  _______),

    [GAMING] = LAYOUT_91_ansi(
        KC_MUTE,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  KC_MUTE,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,  KC_LCTL,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  KC_SCLN,  _______,             _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,
        _______,  _______,  _______,  _______,  KC_NO,              _______,                       _______,            KC_NO,    _______,   _______,  _______,  _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [DEFAULT] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB)) },
    [OVERLAY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLL, MS_WHLR) },
    [GAMING]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif // ENCODER_MAP_ENABL
