//License Header

//Documentation: https://docs.qmk.fm/features/rgb_matrix#custom-rgb-matrix-effects
RGB_MATRIX_EFFECT(cool_layer_anim)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "keymap.h"

static void cool_layer_anim_init(void);

static hsv_t get_adjusted_color(uint8_t hue, uint8_t saturation, uint8_t value);

static bool is_tap_key(uint8_t key);
static bool is_hot_key(uint8_t key);
static bool is_movement_key(uint8_t key);
static bool is_overlay_key(uint8_t key);

static hsv_t animation(hsv_t color, uint8_t i, uint8_t time);

static bool cool_layer_anim(effect_params_t* params)
{
    if (params->init) cool_layer_anim_init();

    uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 4, 1));
    bool has_overlay = layer_state_is(OVERLAY);
    bool has_gaming = layer_state_is(GAMING);

    hsv_t reg_color = get_adjusted_color(5, 255, 240);
    hsv_t tap_color = get_adjusted_color(7, 240, 255);
    hsv_t hot_color = get_adjusted_color(8, 200, 160);

    if (has_gaming)
    {
        reg_color = get_adjusted_color(165, 255, 130);
        tap_color = get_adjusted_color(145, 230, 100);
        hot_color = get_adjusted_color(120, 25, 255);
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++)
    {
        RGB_MATRIX_TEST_LED_FLAGS();
        hsv_t color = reg_color;
        bool animate = false;

        if (is_tap_key(i))
        {
            color = tap_color;
            animate = true;
        }

        bool hot = is_hot_key(i) ||
            (has_overlay && is_overlay_key(i)) ||
            (has_gaming && is_movement_key(i));

        if (hot)
        {
            color = hot_color;
            animate = false;
        }

        if (animate) color = animation(color, i, time);
        rgb_t converted = rgb_matrix_hsv_to_rgb(color);
        rgb_matrix_set_color(i, converted.r, converted.g, converted.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#define KEY_COUNT SNLED27351_LED_COUNT
_Static_assert(KEY_COUNT == RGB_MATRIX_LED_COUNT, "LED light count mismatch!");

static uint8_t KeyRandom[KEY_COUNT];

//Attribute bits:
//  0: a tap key (one of the inner grayer keys)
//  1: a hot key (one of the two red keys, enter or escape)
//  2: a movement key (WASD and arrow keys)
//  3: an overlay key (from normal mode, keys modified when overlay is activated)
static uint8_t KeyAttributes[KEY_COUNT] =
{
    0b00000010 /* ESC */, 0b00000001 /* F1 */,       0b00000001 /* F2 */,    0b00000001 /* F3 */,    0b00000001 /* F4 */, 0b00000000 /* F5 */,    0b00000000 /* F6 */,
    0b00000000 /* M1 */,  0b00000000 /* `~ */,       0b00000001 /* 1! */,    0b00000001 /* 2@ */,    0b00000001 /* 3# */, 0b00000001 /* 4$ */,    0b00000001 /* 5% */, 0b00000001 /* 6^ */,
    0b00000000 /* M2 */,  0b00000000 /* TAB */,      0b00000001 /* Q */,     0b00000101 /* W */,     0b00000001 /* E */,  0b00000001 /* R */,     0b00000001 /* T */,
    0b00000000 /* M3 */,  0b00000000 /* CapsLock */, 0b00000101 /* A */,     0b00000101 /* S */,     0b00000101 /* D */,  0b00000001 /* F */,     0b00000001 /* G */,
    0b00000000 /* M4 */,  0b00000000 /* Shift_L */,  0b00000001 /* Z */,     0b00000001 /* X */,     0b00000001 /* C */,  0b00000001 /* V */,     0b00000001 /* B */,
    0b00000000 /* M5 */,  0b00000000 /* Ctrl_L */,   0b00000000 /* Win_L */, 0b00000000 /* Alt_L */, 0b00000000 /* Fn */, 0b00000100 /* Space */,

    0b00000000 /* F7 */,    0b00000000 /* F8 */,    0b00000001 /* F9 */, 0b00000001 /* F10 */,    0b00000001 /* F11 */,  0b00000001 /* F12 */,     0b00000000 /* INS */,       0b00000000 /* DEL */,
    0b00000001 /* 7& */,    0b00000001 /* 8* */,    0b00000001 /* 9( */, 0b00000001 /* 0) */,     0b00000001 /* -_ */,   0b00000001 /* =+ */,      0b00000000 /* BackSpace */, 0b00000000 /* PgUp */,
    0b00000001 /* Y */,     0b00000001 /* U */,     0b00000001 /* G */,  0b00000001 /* O */,      0b00000001 /* P */,    0b00000001 /* [ */,       0b00000001 /* ] */,         0b00000000 /* \| */,   0b00000000 /* PgDn */,
    0b00000001 /* H */,     0b00000001 /* J */,     0b00000001 /* K */,  0b00000001 /* L */,      0b00000001 /* ;: */,   0b00000001 /* '" */,      0b00000010 /* Enter */,     0b00000000 /* Home */,
    0b00000001 /* N */,     0b00000001 /* M */,     0b00000001 /* ,< */, 0b00000001 /* .> */,     0b00000001 /* ?/ */,   0b00000000 /* Shift_R */, 0b00000101 /* Up */,
    0b00000100 /* Space */, 0b00000000 /* Win_R */, 0b00000000 /* Fn */, 0b00000000 /* Ctrl_R */, 0b00000101 /* Left */, 0b00000101 /* Down */,    0b00000101 /* Right */,
};

static void cool_layer_anim_init(void)
{
    for (uint8_t i = 0; i < KEY_COUNT; ++i)
    {
        KeyRandom[i] = random8();

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row)
        for (uint8_t col = 0; col < MATRIX_COLS; ++col)
        {
            if (g_led_config.matrix_co[row][col] != i) continue;
            if (keymaps[OVERLAY][row][col] != KC_TRNS) KeyAttributes[i] |= (1 << 3);
            break;
        }
    }
}

static hsv_t get_adjusted_color(uint8_t hue, uint8_t saturation, uint8_t value)
{
    hsv_t color;
    color.h = hue;
    color.s = saturation;
    color.v = scale8(value, rgb_matrix_get_val());
    return color;
}

static bool has_attribute(uint8_t key, uint8_t bit)
{
    if (key >= KEY_COUNT) return false;
    return (KeyAttributes[key] & (1 << bit)) != 0;
}

static bool is_tap_key(uint8_t key) { return has_attribute(key, 0); }
static bool is_hot_key(uint8_t key) { return has_attribute(key, 1); }
static bool is_movement_key(uint8_t key) { return has_attribute(key, 2); }
static bool is_overlay_key(uint8_t key) { return has_attribute(key, 3); }

static hsv_t animation(hsv_t color, uint8_t i, uint8_t time)
{
    uint8_t wave = cubicwave8(time + KeyRandom[i] / 2 + i * 3);
    uint8_t brightness = lerp8by8(160, 255, wave);
    color.v = scale8(color.v, brightness);
    return color;
}

#endif

