//License Header

#pragma once
#include QMK_KEYBOARD_H

enum layers
{
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

//Shortcuts
#define LK_SCRN LGUI(KC_L) //Works on Ubuntu and Windows
#define TAB_SWT LALT(KC_TAB)

extern const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS];

