#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// You can also skip layer-names entirely and just use numbers.
#define _QWERTY 0
#define _ESS 1 //Enter Symbol Switch
#define _HOMEMOD 2
#define _FN 3
#define _SYM 4
#define _SYM_ESS 5
#define _SPARE 6
#define _CFG 7//config

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    ESS,
    HOMEMOD,
    FN,
    SYM,
    SYM_ESS,
    SPARE,
    CONFIG,
};

// Shortcut to make keymap more readable
#define KC_FN MO(_FN)
/*
#define KC_ALAS LALT_T(KC_PAST)
#define KC_CTPL LCTL_T(KC_BSLS)

#define KC_NAGR LT(_NUM, KC_GRV)
#define KC_NAMI LT(_NUM, KC_MINS)

#define KC_ADEN LT(_SPARE, KC_END)
#define KC_ADPU LT(_SPARE, KC_PGUP)
*/

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSPO:
            // Do not force the mod-tap key press to be handled as a modifier
            // if any other key was pressed while the mod-tap key is held down.
            return false;
//        case MT(MOD_LSFT,KC_9):
//            return false;
        case KC_RSPC:
            return false;
        default:
            // Force the mod-tap key press to be handled as a modifier if any
            // other key was pressed while the mod-tap key is held down.
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _ESS, _SYM, _SYM_ESS);
}

const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
{ {0, 5},  {1, 5},  {2, 5},  {3, 5}, {4, 5}, {5, 5}, {6, 5}},
{ {0, 6},  {1, 6},  {2, 6},  {3, 6}, {4, 6}, {5, 6}, {6, 6}},
{ {0, 2},  {1, 7},  {2, 7},  {3, 7}, {4, 7}, {5, 7}, {6, 7}}, // caps won't be switched, because of extend
{ {0, 8},  {1, 8},  {2, 8},  {3, 8}, {4, 8}, {5, 8}, {6, 8}},
{ {0, 9},  {1, 9},  {2, 9},  {3, 9}, {4, 9}, {5, 9}, {6, 9}},

{ {0, 0},  {1, 0},  {2, 0},  {3, 0}, {4, 0}, {5, 0}, {6, 0}},
{ {0, 1},  {1, 1},  {2, 1},  {3, 1}, {4, 1}, {5, 1}, {6, 1}},
{ {0, 2},  {1, 2},  {2, 2},  {3, 2}, {4, 2}, {5, 2}, {6, 2}},
{ {0, 3},  {1, 3},  {2, 3},  {3, 3}, {4, 3}, {5, 3}, {6, 3}},
{ {0, 4},  {1, 4},  {2, 4},  {3, 4}, {4, 4}, {5, 4}, {6, 4}},
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SH_T(KC_SPC):
            return TAPPING_TERM + 300;
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
// ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    QK_GESC ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_NO   ,                          KC_NO   ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_BSPC ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_LBRC ,                          KC_RBRC ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_QUOT ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_CAPS ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_EQL  ,                          KC_MINS ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_ENT  ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_LSPO ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,SH_OS   ,                          KC_NO   ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSPC ,
// ├────────┼────────┼────────┴─┬──────┴───┬────┴────────┼────────┤                         ├────────┼────────┴────┬───┴──────┬─┴────────┼────────┼────────┤
    KC_LCTL ,KC_LCPO ,KC_LGUI   ,KC_LALT   ,SH_T(KC_SPC) ,MO(_SYM),                          MO(_SYM),KC_SPC       ,KC_RALT   ,MO(_FN)   ,KC_RCPC ,KC_RCTL
// └────────┴────────┴──────────┴──────────┴─────────────┴────────┘                         └────────┴─────────────┴──────────┴──────────┴────────┴────────┘
),

[_ESS] = LAYOUT(
// ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_BSLS ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┴─┬──────┴───┬────┴────────┼────────┤                         ├────────┼────────┴────┬───┴──────┬─┴────────┼────────┼────────┤
    _______ ,_______ ,_______   ,_______   ,_______      ,_______ ,                          _______ ,_______      ,_______   ,_______   ,_______ ,_______
// └────────┴────────┴──────────┴──────────┴─────────────┴────────┘                         └────────┴─────────────┴──────────┴──────────┴────────┴────────┘
),

[_HOMEMOD] = LAYOUT(
// ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
_______ ,_______ ,RALT_T(KC_S),LCTL_T(KC_D),LSFT_T(KC_F),LT(_SYM,KC_G),_______ ,           _______ ,LT(_SYM,KC_H),RSFT_T(KC_J),RCTL_T(KC_K),LALT_T(KC_L),_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    KC_LSFT ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_RSFT ,
// ├────────┼────────┼────────┴─┬──────┴───┬────┴────────┼────────┤                         ├────────┼────────┴────┬───┴──────┬─┴────────┼────────┼────────┤
    _______ ,_______ ,_______   ,_______   ,_______      ,_______ ,                          _______ ,_______      ,_______   ,_______   ,_______ ,_______
// └────────┴────────┴──────────┴──────────┴─────────────┴────────┘                         └────────┴─────────────┴──────────┴──────────┴────────┴────────┘
),

[_FN] = LAYOUT(
// ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_DEL ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_PIPE ,_______ ,                          _______ ,KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,KC_PSCR ,XXXXXXX ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,KC_HASH ,KC_DLR  ,KC_LBRC ,KC_RBRC ,KC_GRV  ,_______ ,                          _______ ,KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RIGHT,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,KC_PERC ,KC_CIRC ,KC_LPRN ,KC_RPRN ,KC_TILD ,_______ ,                          _______ ,KC_MSEL ,KC_MPLY ,KC_MPRV ,KC_MNXT ,KC_MPLY ,_______ ,
// ├────────┼────────┼────────┴─┬──────┴───┬────┴────────┼────────┤                         ├────────┼────────┴────┬───┴──────┬─┴────────┼────────┼────────┤
    _______ ,_______ ,_______   ,_______   ,_______      ,_______ ,                          _______ ,_______      ,_______   ,_______   ,_______ ,_______
// └────────┴────────┴──────────┴──────────┴─────────────┴────────┘                         └────────┴─────────────┴──────────┴──────────┴────────┴────────┘
),

[_SYM] = LAYOUT(
// ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    KC_GRV  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F11  ,                          KC_F12  ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_DEL ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,_______ ,                          _______ ,KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,KC_BSLS ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    CAPSWRD ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,_______ ,                          _______ ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,KC_MSEL ,KC_MPLY ,XXXXXXX , KC_MPRV, KC_MNXT,_______ ,                          _______ ,KC_MSEL ,KC_MPLY , KC_MPRV, KC_MNXT,KC_MPLY ,_______ ,
// ├────────┼────────┼────────┴─┬──────┴───┬────┴────────┼────────┤                         ├────────┼────────┴────┬───┴──────┬─┴────────┼────────┼────────┤
    RESET   ,_______ ,_______   ,_______   ,_______      ,TG(_CFG),                          TG(_CFG),_______      ,_______   ,_______   ,_______ ,RESET
// └────────┴────────┴──────────┴──────────┴─────────────┴────────┘                         └────────┴─────────────┴──────────┴──────────┴────────┴────────┘
),

[_SYM_ESS] = LAYOUT(
// ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,XXXXXXX ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_QUOT ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,KC_EQL  ,KC_PLUS ,_______ ,                          _______ ,KC_UNDS ,KC_MINS ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┴─┬──────┴───┬────┴────────┼────────┤                         ├────────┼────────┴────┬───┴──────┬─┴────────┼────────┼────────┤
    _______ ,_______ ,_______   ,_______   ,_______      ,_______ ,                          _______ ,_______      ,_______   ,_______   ,_______ ,_______
// └────────┴────────┴──────────┴──────────┴─────────────┴────────┘                         └────────┴─────────────┴──────────┴──────────┴────────┴────────┘
),

[_CFG] = LAYOUT(
// ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    TG(_CFG),TG(_ESS),TG(_HOMEMOD),_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_1    ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┴─┬──────┴───┬────┴────────┼────────┤                         ├────────┼────────┴────┬───┴──────┬─┴────────┼────────┼────────┤
    _______ ,_______ ,_______   ,_______   ,_______      ,_______ ,                          _______ ,_______      ,_______   ,_______   ,_______ ,_______
// └────────┴────────┴──────────┴──────────┴─────────────┴────────┘                         └────────┴─────────────┴──────────┴──────────┴────────┴────────┘
),

[_SPARE] = LAYOUT(
// ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,XXXXXXX ,                          XXXXXXX ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    XXXXXXX ,RESET   ,RGB_M_P ,RGB_TOG ,RGB_MOD ,RGB_HUD ,RGB_HUI ,                          RGB_SAD ,RGB_SAI ,RGB_VAD ,RGB_VAI ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX  ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
// ├────────┼────────┼────────┴─┬──────┴───┬────┴────────┼────────┤                         ├────────┼────────┴────┬───┴──────┬─┴────────┼────────┼────────┤
    XXXXXXX ,XXXXXXX ,XXXXXXX   ,XXXXXXX   ,XXXXXXX      ,XXXXXXX ,                          XXXXXXX ,XXXXXXX      ,XXXXXXX   ,XXXXXXX   ,XXXXXXX ,XXXXXXX
// └────────┴────────┴──────────┴──────────┴─────────────┴────────┘                         └────────┴─────────────┴──────────┴──────────┴────────┴────────┘
)
};

/*
[_] = LAYOUT(
// ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
// ├────────┼────────┼────────┴─┬──────┴───┬────┴────────┼────────┤                         ├────────┼────────┴────┬───┴──────┬─┴────────┼────────┼────────┤
    _______ ,_______ ,_______   ,_______   ,_______      ,_______ ,                          _______ ,_______      ,_______   ,_______   ,_______ ,_______
// └────────┴────────┴──────────┴──────────┴─────────────┴────────┘                         └────────┴─────────────┴──────────┴──────────┴────────┴────────┘
),
 */