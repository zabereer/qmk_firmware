#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/* use UK keymap */

#define UK_HASH KC_NONUS_HASH
#define UK_BSLS KC_NONUS_BSLASH

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers and hex
#define CRSR 3 // cursor keys
#define MOUS 4 // mouse keys
#define KEYW 5 // keyword macros

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

// user macros
#define UM_0x M(1)
#define UM_PUB M(2)
#define UM_PRO M(3)
#define UM_PRV M(4)
#define UM_CLS M(5)
#define UM_STR M(6)
#define UM_RET M(7)
#define UM_INC M(8)
#define UM_OBJ M(9)
#define UM_GITLOG M(10)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  | SfLt |           | SfRt |   6  |   7  |   8  |   9  |   0  | BkSp   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  | Del    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Caps?  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | Enter  |
 * |--------+------+------+------+------+------|  L2  |           | Ins  |------+------+------+------+------+--------|
 * | LSft/( |   Z  |   X  |   C  | V/L3 | B/L4 |      |           |      | N/L4 | M/L3 |   ,  |   .  |   /  | RSft/) |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Ctrl/[| Alt/{|   #  | Left |Right |                                       | Down |  Up  |   -  | Alt/}|Ctrl/]|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | [/L5 |  {   |       |   }  | ]/L5 |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Space| BkSp | Home |       | PgUp | Enter|Space |
 *                                 |  /   |  /   |------|       |------|   /  |  /   |
 *                                 | Ctrl | Alt  | End  |       | PgDn |  Alt | Ctrl |
 *                                 `--------------------'       `--------------------'
 */
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,            KC_2,       KC_3,      KC_4,           KC_5,           LSFT(KC_LEFT),
        KC_TAB,         KC_Q,            KC_W,       KC_E,      KC_R,           KC_T,           MO(SYMB),
        KC_CAPS,        KC_A,            KC_S,       KC_D,      KC_F,           KC_G,
        KC_LSPO,        KC_Z,            KC_X,       KC_C,      LT(CRSR, KC_V), LT(MOUS, KC_B), TG(NUMB),
        CTL_T(KC_LBRC), ALT_T(KC_LCBR),  UK_HASH,    KC_LEFT,   KC_RGHT,
                                                                                 LT(KEYW, KC_LBRC),  KC_LCBR,
                                                                                                     KC_HOME,
                                                                 CTL_T(KC_SPC),  ALT_T(KC_BSPC),     KC_END,
        // right hand
             LSFT(KC_RGHT),  KC_6,            KC_7,            KC_8,      KC_9,       KC_0,             KC_BSPC,
             MO(SYMB),       KC_Y,            KC_U,            KC_I,      KC_O,       KC_P,             KC_DELT,
                             KC_H,            KC_J,            KC_K,      KC_L,       KC_SCLN,          KC_ENT,
             KC_INS,         LT(MOUS, KC_N),  LT(CRSR, KC_M),  KC_COMM,   KC_DOT,     KC_SLSH,          KC_RSPC,
                                              KC_DOWN,         KC_UP,     KC_MINS,    ALT_T(KC_RCBR),   CTL_T(KC_RBRC),
           KC_RCBR,    LT(KEYW, KC_RBRC),
           KC_PGUP,
           KC_PGDN,    ALT_T(KC_ENT),      CTL_T(KC_SPC)
    ),
/* Keymap 1: Symbol Layer with F keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ##   |  F1  |  F2  |  F3  |  F4  |  F5  |  ##  |           |  ##  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ##   |   !  |   "  |   £  |   $  |   %  |  ##  |           |  ##  |   -  |   +  |   :  |   @  |   ~  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ##   |   ^  |   &  |   *  |   _  |   #  |------|           |------|   *  |   /  |   ;  |   '  |   #  |   ##   |
 * |--------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+--------|
 * |   ##   |   \  |   |  |   `  |   -  |   /  |      |           |      |   =  |   %  |   <  |   >  |   ?  |   ##   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  ##  |  ##  |  ##  |  ##  |  ##  |                                       |  ##  |  ##  |  ##  |  ##  |  ##  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = KEYMAP(
        // left hand
        KC_TRNS,   KC_F1,       KC_F2,       KC_F3,       KC_F4,          KC_F5,       KC_TRNS,
        KC_TRNS,   KC_EXLM,     LSFT(KC_2),  LSFT(KC_3),  LSFT(KC_4),     LSFT(KC_5),  KC_TRNS,
        KC_TRNS,   LSFT(KC_6),  LSFT(KC_7),  LSFT(KC_8),  LSFT(KC_MINS),  UK_HASH,
        KC_TRNS,   UK_BSLS,     KC_PIPE,     KC_GRV,      KC_MINS,        KC_SLSH,     KC_TRNS,
        KC_TRNS,   KC_TRNS,     KC_TRNS,     KC_TRNS,     KC_TRNS,
                                                                            KC_TRNS,   KC_TRNS,
                                                                                       KC_TRNS,
                                                                 KC_TRNS,   KC_TRNS,   KC_TRNS,
        // right hand
             KC_TRNS,   KC_F6,       KC_F7,       KC_F8,          KC_F9,          KC_F10,         KC_F11,
             KC_TRNS,   KC_MINS,     KC_PLUS,     LSFT(KC_SCLN),  LSFT(KC_QUOT),  LSFT(UK_HASH),  KC_F12,
                        KC_ASTR,     KC_SLSH,     KC_SCLN,        KC_QUOT,        UK_HASH,        KC_TRNS,
             KC_TRNS,   KC_EQL,      LSFT(KC_5),  LSFT(KC_COMM),  LSFT(KC_DOT),   LSFT(KC_SLSH),  KC_TRNS,
                                     KC_TRNS,     KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,
           KC_TRNS,   KC_TRNS,
           KC_TRNS,
           KC_TRNS,   KC_TRNS,  KC_TRNS
    ),
/* Keymap 2: Numerics and hex
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |   ##    |  A   |  B   |  C   |  D   |  E   |  F   |           |  A   |  B   |  C   |  D   |   E  |   F  |   ##   |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ##    |  *   |  7   |  8   |  9   |  *   |  0x  |           |  0x  |  *   |   7  |   8  |   9  |   *  |   ##   |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ##    |  /   |  4   |  5   |  6   |  /   |------|           |------|  /   |   4  |   5  |   6  |   /  |   ##   |
 * |---------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+--------|
 * |   ##    |  -   |  1   |  2   |  3   |  -   |      |           |      |  -   |   1  |   2  |   3  |   -  |   ##   |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   =   |  +   |  0   |  ,   |  .   |                                       |   0  |   ,  |   .  |   +  |  =   |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NUMB] = KEYMAP(
        // left hand
        KC_TRNS,   KC_A,        KC_B,        KC_C,        KC_D,           KC_E,        KC_F,
        KC_TRNS,   KC_ASTR,     KC_7,        KC_8,        KC_9,           KC_ASTR,     UM_0x,
        KC_TRNS,   KC_SLSH,     KC_4,        KC_5,        KC_6,           KC_SLSH,
        KC_TRNS,   KC_MINS,     KC_1,        KC_2,        KC_3,           KC_MINS,     KC_TRNS,
        KC_EQL,    KC_PLUS,     KC_0,        KC_COMM,     KC_DOT,
                                                                            KC_TRNS,   KC_TRNS,
                                                                                       KC_TRNS,
                                                                 KC_TRNS,   KC_TRNS,   KC_TRNS,
        // right hand
             KC_A,      KC_B,        KC_C,        KC_D,           KC_E,           KC_F,           KC_TRNS,
             UM_0x,     KC_ASTR,     KC_7,        KC_8,           KC_9,           KC_ASTR,        KC_TRNS,
                        KC_SLSH,     KC_4,        KC_5,           KC_6,           KC_SLSH,        KC_TRNS,
             KC_TRNS,   KC_MINS,     KC_1,        KC_2,           KC_3,           KC_MINS,        KC_TRNS,
                                     KC_0,        KC_COMM,        KC_DOT,         KC_PLUS,        KC_EQL,
           KC_TRNS,   KC_TRNS,
           KC_TRNS,
           KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
/* Keymap 3: Cursor movement
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |  Up  |      |      |      |           |      |      |      |  Up  |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      | Left | Down | Right|      |------|           |------|      | Left | Down | Right|      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |  Up  |      | Down |  ##  |      |      |           |      |      |  ##  | Down |      |  Up  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Left  | Down | Right|      |      |                                       |      |      | Left | Down | Right|
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[CRSR] = KEYMAP(
        // left hand
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_UP,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_NO,
        KC_NO,     KC_UP,     KC_NO,     KC_DOWN,   KC_TRNS,   KC_NO,     KC_NO,
        KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_NO,     KC_NO,
                                                                   KC_NO,   KC_NO,
                                                                            KC_NO,
                                                          KC_NO,   KC_NO,   KC_NO,
        // right hand
             KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     KC_NO,     KC_NO,     KC_UP,     KC_NO,     KC_NO,     KC_NO,
                        KC_NO,     KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_NO,     KC_NO,
             KC_NO,     KC_NO,     KC_TRNS,   KC_DOWN,   KC_NO,     KC_UP,     KC_NO,
                                   KC_NO,     KC_NO,     KC_LEFT,   KC_DOWN,   KC_RGHT,
           KC_NO,   KC_NO,
           KC_NO,
           KC_NO,   KC_NO,   KC_NO
    ),
/* Keymap 4: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |      |      |           |      |      | Lclk | MsUp | Rclk |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |MsLeft|MsDown|MsRght|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Lclk  | MsUp | Rclk |MsDown|      |  ##  |      |           |      |  ##  |      |MsDown| Lclk | MsUp | Rclk   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |MsLeft|MsDown|MsRight      |      |                                       |      |      |MsLeft|MsDown|MsRght|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MOUS] = KEYMAP(
        // left hand
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_NO,
        KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_MS_D,   KC_NO,     KC_TRNS,   KC_NO,
        KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_NO,     KC_NO,
                                                                   KC_NO,   KC_NO,
                                                                            KC_NO,
                                                          KC_NO,   KC_NO,   KC_NO,
        // right hand
             KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     KC_NO,     KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_NO,     KC_NO,
                        KC_NO,     KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_NO,     KC_NO,
             KC_NO,     KC_TRNS,   KC_NO,     KC_MS_D,   KC_BTN1,   KC_MS_U,   KC_BTN2,
                                   KC_NO,     KC_NO,     KC_MS_L,   KC_MS_D,   KC_MS_R,
           KC_NO,   KC_NO,
           KC_NO,
           KC_NO,   KC_NO,   KC_NO
    ),
/* Keymap 5: Keywords
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |  ret |      |      |           |      |      |      |  prv |  pro | pub  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |  str |  obj |      | gitl |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |  cls |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |  inc |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |      |       |      |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[KEYW] = KEYMAP(
        // left hand
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     UM_RET,    KC_NO,     KC_NO,
        KC_NO,     KC_NO,     UM_STR,    UM_OBJ,    KC_NO,     UM_GITLOG,
        KC_NO,     KC_NO,     KC_NO,     UM_CLS,    KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     UM_INC,    KC_NO,     KC_NO,
                                                                   KC_TRNS,   KC_NO,
                                                                              KC_NO,
                                                          KC_NO,   KC_NO,     KC_NO,
        // right hand
             KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     KC_NO,     KC_NO,     UM_PRV,    UM_PRO,    UM_PUB,    KC_NO,
                        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
                                   KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
           KC_NO,   KC_TRNS,
           KC_NO,
           KC_NO,   KC_NO,     KC_NO
    ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
    case 0:
        if (record->event.pressed) {
            SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
    case 1:
        if (record->event.pressed) {
            return MACRO(T(0), T(X), END);
        }
        break;
    case 2:
        if (record->event.pressed) {
            SEND_STRING("public");
        }
        break;
    case 3:
        if (record->event.pressed) {
            SEND_STRING("protected");
        }
        break;
    case 4:
        if (record->event.pressed) {
            SEND_STRING("private");
        }
        break;
    case 5:
        if (record->event.pressed) {
            return MACRO(T(C), T(L), T(A), T(S), T(S),
                         T(ENT), D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         T(P), T(U), T(B), T(L), T(I), T(C),
                         D(LSFT), T(SCLN), U(LSFT), T(ENT), T(ENT),
                         T(P), T(R), T(I), T(V), T(A), T(T), T(E),
                         D(LSFT), T(SCLN), U(LSFT), T(ENT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(ENT), END);
            /* SEND_STRING("class"); */
        }
        break;
    case 6:
        if (record->event.pressed) {
            SEND_STRING("struct");
        }
        break;
    case 7:
        if (record->event.pressed) {
            SEND_STRING("return");
        }
        break;
    case 8:
        if (record->event.pressed) {
            SEND_STRING("#include");
        }
        break;
    case 9:
        if (record->event.pressed) {
            SEND_STRING("objdump -CT -x -d");
        }
        break;
    case 10:
        if (record->event.pressed) {
            SEND_STRING("git log --oneline --graph --decorate=short");
        }
        break;
    }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

};
