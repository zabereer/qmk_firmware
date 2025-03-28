#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include <stdarg.h>

/* use UK keymap */

#define UK_HASH KC_NONUS_HASH
#define UK_BSLS KC_NONUS_BSLASH
#define UK_PIPE LSFT(UK_BSLS)

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers and hex
#define CRSR 3 // cursor keys
#define MOUS 4 // mouse keys
#define KEYW 5 // keyword macros
#define EMAC 6 // emacs

// my macros
#define UM_ECET   M(0)  // { }
#define UM_0x     M(1)
#define UM_PUB    M(2)
#define UM_PRO    M(3)
#define UM_PRV    M(4)
#define UM_SYSCTL M(5)
#define UM_STD    M(6)
#define UM_RET    M(7)
#define UM_INC    M(8)
#define UM_OBJ    M(9)
#define UM_GITLOG M(10)
#define UM_GOODM  M(11)
#define UM_NAMESP M(12)
#define UM_EML    M(13)
#define UM_EMTR   M(14) // emacs toggle read-only
#define UM_EMWR   M(15) // emacs write buffer (save)
#define UM_EMUN   M(16) // emacs undo
#define UM_EMRE   M(17) // emacs redo
#define UM_EMPB   M(18) // emacs previous buffer
#define UM_EMNB   M(19) // emacs next buffer
#define UM_GOODN  M(20)
#define UM_MTCA   M(21)
#define UM_ECETS  M(22)  // { };
#define UM_TMPL   M(23)
#define UM_TYPN   M(24)
#define UM_NULLP  M(25)
#define UM_BOOL   M(26)
#define UM_CONST  M(27)
#define UM_SMILY  M(28)
#define UM_SADF   M(29)
#define UM_SCARF  M(30)
#define UM_DECAF  M(31)
#define UM_EMCSNW M(32)
#define UM_LESS   M(33)
#define UM_EXPL   M(34)
#define UM_VIRT   M(35)
#define UM_EMFB   M(36) // emacs font bigger
#define UM_EMFS   M(37) // emacs font smaller
#define UM_AUTO   M(38)
#define UM_EMIND  M(39) // emacs indent region
#define UM_EMKILL M(40) // emacs kill buffer
#define UM_WINK   M(41)
#define UM_EMDW   M(42) // emacs delete window
#define UM_EMSB   M(43) // emacs select buffer
#define UM_EMDE   M(44) // emacs dired
#define UM_EMX2   M(45) // emacs C-x 2
#define UM_EMX3   M(46) // emacs C-x 3
#define UM_EMX52  M(47) // emacs C-x 5 2
#define UM_EMX50  M(48) // emacs C-x 5 0
#define UM_EMX1   M(49) // emacs C-x 1
#define UM_GOODA  M(50)
#define UM_ROLEYE M(51)
#define UM_CXO    M(52) // emacs C-x o
#define UM_CSE    M(53) // VSCode Ctl + Shft + E (explorer)
#define UM_TERM   M(54) // VSCode Ctl + ` (terminal)
#define UM_CEXPR  M(55)
#define UM_UP10   M(56)
#define UM_DN10   M(57)
#define UM_RT10   M(58)
#define UM_LT10   M(59)
#define UM_UP20   M(60)
#define UM_DN20   M(61)
#define UM_RT20   M(62)
#define UM_LT20   M(63)
#define UM_STATIC M(64)
#define UM_PLESS  M(65)
#define UM_NODIS  M(66)
#define UM_HELLO  M(67)
#define UM_GOODE  M(68)
#define UM_JNCTL  M(69)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC/GRV|   1  |   2  |   3  |   4  |   5  |  L2  |           |  L2  |   6  |   7  |   8  |   9  |   0  | BkSp   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  | Del    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Caps/L2|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |Enter/L2|
 * |--------+------+------+------+------+------|  L6  |           |  L6  |------+------+------+------+------+--------|
 * |  LSft  |   Z  |   X  |   C  | V/L3 | B/L4 |      |           |      | N/L4 | M/L3 |   ,  |   .  |   /  |  RSft  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Ctrl/[| Alt/]|   #  | Left |Right |                                       |  Up  | Down |   -  | Alt/[|Ctrl/]|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |   \  | lead |       | lead |  Ins |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Space| BkSp | Home |       | PgUp | Enter|Space |
 *                                 |  /   |  /   |------|       |------|   /  |  /   |
 *                                 | Ctrl | Alt  |End/L5|       |PDn/L5|  Alt | Ctrl |
 *                                 `--------------------'       `--------------------'
 */
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_GESC,           KC_1,            KC_2,       KC_3,      KC_4,           KC_5,           MO(NUMB),
        KC_TAB,            KC_Q,            KC_W,       KC_E,      KC_R,           KC_T,           MO(SYMB),
        MO(NUMB),          KC_A,            KC_S,       KC_D,      KC_F,           KC_G,
        KC_LSFT,           KC_Z,            KC_X,       KC_C,      LT(CRSR, KC_V), LT(MOUS, KC_B), MO(EMAC),
        CTL_T(KC_LBRC),    ALT_T(KC_RBRC),  UK_HASH,    KC_LEFT,   KC_RGHT,
                                                                                     UK_BSLS,         KC_LEAD,
                                                                                                      KC_HOME,
                                                                     CTL_T(KC_SPC),  ALT_T(KC_BSPC),  LT(KEYW, KC_END),
        // right hand
             MO(NUMB),        KC_6,            KC_7,            KC_8,      KC_9,       KC_0,             KC_BSPC,
             MO(SYMB),        KC_Y,            KC_U,            KC_I,      KC_O,       KC_P,             KC_DEL,
                              KC_H,            KC_J,            KC_K,      KC_L,       KC_SCLN,          LT(NUMB, KC_ENT),
             MO(EMAC),        LT(MOUS, KC_N),  LT(CRSR, KC_M),  KC_COMM,   KC_DOT,     KC_SLSH,          KC_RSFT,
                                               KC_UP,           KC_DOWN,   KC_MINS,    ALT_T(KC_LBRC),   CTL_T(KC_RBRC),
           KC_LEAD,            KC_INS,
           KC_PGUP,
           LT(KEYW, KC_PGDN),  ALT_T(KC_ENT),   CTL_T(KC_SPC)
    ),
/* Keymap 1: Symbol Layer with F keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |  F1  |  F2  |  F3  |  F4  |  F5  |  ##  |           |  ##  |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ##   |   !  |   "  |   £  |   $  |   %  |  ##  |           |  ##  |   +  |   -  |   =  |   @  |   ~  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  CAPS  |   ^  |   &  |   *  |   _  |   #  |------|           |------|   {  |   }  |   ;  |   '  |   #  |   ##   |
 * |--------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+--------|
 * |   ##   |   \  |   |  |   `  |   -  |   /  |      |           |      |   [  |   ]  |   <  |   >  |   ?  |   ##   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  (   |   )  |  ##  | Home | End  |                                       | PgUp | PgDn |  ##  |   (  |   )  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
        // left hand
        KC_GRV,     KC_F1,       KC_F2,       KC_F3,       KC_F4,          KC_F5,       KC_TRNS,
        KC_TRNS,    KC_EXLM,     LSFT(KC_2),  LSFT(KC_3),  LSFT(KC_4),     LSFT(KC_5),  KC_TRNS,
        KC_CAPS,    LSFT(KC_6),  LSFT(KC_7),  LSFT(KC_8),  LSFT(KC_MINS),  UK_HASH,
        KC_TRNS,    UK_BSLS,     UK_PIPE,     KC_GRV,      KC_MINS,        KC_SLSH,     KC_TRNS,
        LSFT(KC_9), LSFT(KC_0),  KC_TRNS,     KC_HOME,     KC_END,
                                                                            KC_TRNS,   KC_TRNS,
                                                                                       KC_TRNS,
                                                                 KC_TRNS,   KC_TRNS,   KC_TRNS,
        // right hand
             KC_TRNS,   KC_F6,       KC_F7,       KC_F8,          KC_F9,          KC_F10,         KC_F11,
             KC_TRNS,   KC_PLUS,     KC_MINS,     KC_EQL,         LSFT(KC_QUOT),  LSFT(UK_HASH),  KC_F12,
                        KC_LCBR,     KC_RCBR,     KC_SCLN,        KC_QUOT,        UK_HASH,        KC_TRNS,
             KC_TRNS,   KC_LBRC,     KC_RBRC,     LSFT(KC_COMM),  LSFT(KC_DOT),   LSFT(KC_SLSH),  KC_TRNS,
                                     KC_PGUP,     KC_PGDN,        KC_TRNS,        LSFT(KC_9),     LSFT(KC_0),
           KC_TRNS,   KC_TRNS,
           KC_TRNS,
           KC_TRNS,   KC_TRNS,  KC_TRNS
    ),
/* Keymap 2: Numerics and hex
 *
 * ,---------------------------------------------------.           ,-------------------------------------------------.
 * |   ##    |  A   |  B   |  C   |  D   |  E   |  F   |           |  A   |  B   |  C   |  D   |   E  |   F  |   ##  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+-------|
 * |   ##    |  +   |  7   |  8   |  9   |  +   |  0x  |           |  0x  |  +   |   7  |   8  |   9  |   +  |   ##  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+-------|
 * |   ##    |  -   |  4   |  5   |  6   |  -   |------|           |------|  -   |   4  |   5  |   6  |   -  |   ##  |
 * |---------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+-------|
 * |   ##    |  *   |  1   |  2   |  3   |  /   |      |           |      |  *   |   1  |   2  |   3  |   /  |   ##  |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+-------'
 *   |   =   |  =   |  0   |  ,   |  .   |                                       |   0  |   ,  |   .  |   =  |  =  |
 *   `-----------------------------------'                                       `---------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  ##  |  ##  |       |  ##  |  ##  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NUMB] = LAYOUT_ergodox(
        // left hand
        KC_TRNS,   KC_A,        KC_B,        KC_C,        KC_D,           KC_E,        KC_F,
        KC_TRNS,   KC_PLUS,     KC_7,        KC_8,        KC_9,           KC_PLUS,     UM_0x,
        KC_TRNS,   KC_MINS,     KC_4,        KC_5,        KC_6,           KC_MINS,
        KC_TRNS,   KC_ASTR,     KC_1,        KC_2,        KC_3,           KC_SLSH,     KC_TRNS,
        KC_EQL,    KC_EQL,      KC_0,        KC_COMM,     KC_DOT,
                                                                            KC_TRNS,   KC_TRNS,
                                                                                       KC_TRNS,
                                                                 KC_TRNS,   KC_TRNS,   KC_TRNS,
        // right hand
             KC_A,      KC_B,        KC_C,        KC_D,           KC_E,           KC_F,           KC_TRNS,
             UM_0x,     KC_PLUS,     KC_7,        KC_8,           KC_9,           KC_PLUS,        KC_TRNS,
                        KC_MINS,     KC_4,        KC_5,           KC_6,           KC_MINS,        KC_TRNS,
             KC_TRNS,   KC_ASTR,     KC_1,        KC_2,           KC_3,           KC_SLSH,        KC_TRNS,
                                     KC_0,        KC_COMM,        KC_DOT,         KC_EQL,         KC_EQL,
           KC_TRNS,   KC_TRNS,
           KC_TRNS,
           KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
/* Keymap 3: Cursor movement
 *
 * ,---------------------------------------------------.           ,-------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |       |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+-------|
 * |         | PgUp |      |  Up  |      | Home |      |           |      | Home |      |  Up  |      | PgUp |       |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+-------|
 * |         | PgDn | Left | Down | Right| End  |------|           |------| End  | Left | Down | Right| PgDn |       |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+-------|
 * |   ##    |  Up  |      | Down |  ##  |      |      |           |      |      |  ##  | Down |      |  Up  |   ##  |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+-------'
 *   | Left  | Down | Right| lt10 | rt10 |                                       | up10 | dn10 | Left | Down | Right|
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |  ##  |  ##  |------|       |------|  ##  |  ##  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[CRSR] = LAYOUT_ergodox(
        // left hand
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_PGUP,   KC_NO,     KC_UP,     KC_NO,     KC_HOME,   KC_NO,
        KC_NO,     KC_PGDN,   KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_END,
        KC_TRNS,   KC_UP,     KC_NO,     KC_DOWN,   KC_TRNS,   KC_NO,     KC_NO,
        KC_LEFT,   KC_DOWN,   KC_RGHT,   UM_LT10,   UM_RT10,
                                                                   KC_NO,     KC_NO,
                                                                              KC_NO,
                                                        KC_TRNS,   KC_TRNS,   KC_NO,
        // right hand
             KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     KC_HOME,   KC_NO,     KC_UP,     KC_NO,     KC_PGUP,   KC_NO,
                        KC_END,    KC_LEFT,   KC_DOWN,   KC_RGHT,   KC_PGDN,   KC_NO,
             KC_NO,     KC_NO,     KC_TRNS,   KC_DOWN,   KC_NO,     KC_UP,     KC_TRNS,
                                   UM_UP10,   UM_DN10,   KC_LEFT,   KC_DOWN,   KC_RGHT,
           KC_NO,   KC_NO,
           KC_NO,
           KC_NO,   KC_TRNS,   KC_TRNS
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
 *   |MsLeft|MsDown|MsRight lt10 | rt10 |                                       | up10 | dn10 |MsLeft|MsDown|MsRght|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MOUS] = LAYOUT_ergodox(
        // left hand
        KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_NO,
        KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_MS_D,   KC_NO,     KC_TRNS,   KC_NO,
        KC_MS_L,   KC_MS_D,   KC_MS_R,   UM_LT10,   UM_RT10,
                                                                   KC_NO,   KC_NO,
                                                                            KC_NO,
                                                          KC_NO,   KC_NO,   KC_NO,
        // right hand
             KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     KC_NO,     KC_BTN1,   KC_MS_U,   KC_BTN2,   KC_NO,     KC_NO,
                        KC_NO,     KC_MS_L,   KC_MS_D,   KC_MS_R,   KC_NO,     KC_NO,
             KC_NO,     KC_TRNS,   KC_NO,     KC_MS_D,   KC_BTN1,   KC_MS_U,   KC_BTN2,
                                   UM_UP10,   UM_DN10,   KC_MS_L,   KC_MS_D,   KC_MS_R,
           KC_NO,   KC_NO,
           KC_NO,
           KC_NO,   KC_NO,   KC_NO
    ),
/* Keymap 5: Keywords
 *
 * ,---------------------------------------------------.           ,-------------------------------------------------.
 * |         |roleye| scarf| sadf | wink | smily|      |           |      | decaf|      |      |      |      |       |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+-------|
 * |         | const|consxp|emacnw|  ret | tmpl |      |           |      | typen| nullp|  prv |  pro | pub  |       |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+-------|
 * |         | auto |  std |  obj |      | gitl |------|           |------| hello| jobps| nodis| less | |less|       |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+-------|
 * |         |static| expl |  cls | virt | bool |      |           | rhdt |namesp| goodm| gooda| goodn| mtca |       |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+-------'
 *   |       |      |  inc | lt10 | rt10 |                                       | up10 | dn10 | goode|      |     |
 *   `-----------------------------------'                                       `---------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | ecet | ecets|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |  ##  |       |  ##  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[KEYW] = LAYOUT_ergodox(
        // left hand
        KC_NO,     UM_ROLEYE, UM_SCARF,  UM_SADF,   UM_WINK,   UM_SMILY,   KC_NO,
        KC_NO,     UM_CONST,  UM_CEXPR,  UM_EMCSNW, UM_RET,    UM_TMPL,    KC_NO,
        KC_NO,     UM_AUTO,   UM_STD,    UM_OBJ,    KC_NO,     UM_GITLOG,
        KC_NO,     UM_STATIC, UM_EXPL,   UM_SYSCTL, UM_VIRT,   UM_BOOL,    KC_NO,
        KC_NO,     KC_NO,     UM_INC,    UM_LT10,   UM_RT10,
                                                                   KC_NO,    KC_NO,
                                                                             KC_NO,
                                                          KC_TRNS, KC_TRNS,  KC_TRNS,
        // right hand
             KC_NO,     UM_DECAF,  KC_NO,     KC_NO,     KC_NO,     KC_NO,     KC_NO,
             KC_NO,     UM_TYPN,   UM_NULLP,  UM_PRV,    UM_PRO,    UM_PUB,    KC_NO,
                        UM_HELLO,  UM_JNCTL,  UM_NODIS,  UM_LESS,   UM_PLESS,  KC_NO,
             UM_EML,    UM_NAMESP, UM_GOODM,  UM_GOODA,  UM_GOODN,  UM_MTCA,   KC_NO,
                                   UM_UP10,   UM_DN10,   UM_GOODE,  KC_NO,     KC_NO,
           UM_ECET,  UM_ECETS,
           KC_NO,
           KC_TRNS,  KC_TRNS, KC_TRNS
    ),
/* Keymap 6: emacs
 *
 * ,---------------------------------------------------.           ,-------------------------------------------------.
 * |  Ctl+`  | emx1 | emx2 | emx3 | emx50| emx52| empb |           | emnb | emfb | emfs |      |      | emdw |       |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+-------|
 * |         | emtr |      |C+S+E |      |      |      |           |      | emun | emre | w-up |c-x-o |      |       |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+-------|
 * |         |      | emwr | emde |      |      |------|           |------|      |w-left|emkill|w-rght|      |       |
 * |---------+------+------+------+------+------|  ##  |           |  ##  |------+------+------+------+------+-------|
 * |         | emind|      |      |      | emsb |      |           |      |      |      |w-down|      |      |       |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+-------'
 *   |       |      |      | lt20 | rt20 |                                       | up20 | dn20 |      |      |     |
 *   `-----------------------------------'                                       `---------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[EMAC] = LAYOUT_ergodox(
        // left hand
        UM_TERM,   UM_EMX1,   UM_EMX2,   UM_EMX3,   UM_EMX50,  UM_EMX52,  UM_EMPB,
        KC_NO,     UM_EMTR,   KC_NO,     UM_CSE,    KC_NO,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     UM_EMWR,   UM_EMDE,   KC_NO,     KC_NO,
        KC_NO,     UM_EMIND,  KC_NO,     KC_NO,     KC_NO,     UM_EMSB,   KC_TRNS,
        KC_NO,     KC_NO,     KC_NO,     UM_LT20,   UM_RT20,
                                                                   KC_NO,   KC_NO,
                                                                            KC_NO,
                                                          KC_NO,   KC_NO,   KC_NO,
        // right hand
             UM_EMNB,   UM_EMFB,  UM_EMFS,        KC_NO,          KC_NO,          UM_EMDW,   KC_NO,
             KC_NO,     UM_EMUN,  UM_EMRE,        LSFT(KC_UP),    UM_CXO,         KC_NO,     KC_NO,
                        KC_NO,    LSFT(KC_LEFT),  UM_EMKILL,      LSFT(KC_RGHT),  KC_NO,     KC_NO,
             KC_TRNS,   KC_NO,    KC_NO,          LSFT(KC_DOWN),  KC_NO,          KC_NO,     KC_NO,
                                  UM_UP20,        UM_DN20,        KC_NO,          KC_NO,     KC_NO,
           KC_NO,   KC_NO,
           KC_NO,
           KC_NO,   KC_NO,   KC_NO
    ),
};

enum next_key_down_up {
    NK_DOWN_UP,
    NK_DOWN,
    NK_UP // a bit of a hack, this works as long as NK_UP < KC_A
};

void send_keystrokes(uint8_t key, ...)
{
    va_list vl;
    va_start(vl, key);
    enum next_key_down_up nkdu = NK_DOWN_UP;
    while (key != KC_NO) {
        if (key < KC_A) {
            nkdu = key;
        } else {
            switch (nkdu) {
            case NK_DOWN_UP:
                register_code(key);
            case NK_UP:
                unregister_code(key);
                break;
            case NK_DOWN:
                register_code(key);
            }
            nkdu = NK_DOWN_UP;
        }
        key = va_arg(vl, int);
    }
    va_end(vl);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
    case 0: // { }
        if (record->event.pressed) {
            return MACRO(T(ENT), D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(UP),
                         T(TAB), END);
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
            SEND_STRING("systemctl --user ");
        }
        break;
    case 6:
        if (record->event.pressed) {
            SEND_STRING("std::");
        }
        break;
    case 7:
        if (record->event.pressed) {
            SEND_STRING("return");
        }
        break;
    case 8: // #include
        if (record->event.pressed) {
            return MACRO(T(NONUS_HASH), T(I), T(N), T(C), T(L), T(U), T(D), T(E), END);
        }
        break;
    case 9:
        if (record->event.pressed) {
            SEND_STRING("objdump -CT -x -D ");
        }
        break;
    case 10:
        if (record->event.pressed) {
            SEND_STRING("git log --oneline --graph --decorate=short ");
        }
        break;
    case 11:
        if (record->event.pressed) {
            SEND_STRING("good morning");
        }
        break;
    case 12:
        if (record->event.pressed) {
            SEND_STRING("namespace");
        }
        break;
    case 13:
        if (record->event.pressed) {
            return MACRO(T(A), T(L), T(B), T(E), T(R), T(T), T(P), T(R), T(E),
                         T(T), T(O), T(R), T(I), T(U), T(S),
                         D(LSFT), T(QUOT), U(LSFT), T(Y), T(A), T(H),
                         T(O), T(O), T(DOT), T(C), T(O), T(DOT), T(U), T(K),
                         END);
        }
        break;
    case 14: // emacs toggle read-only
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(Q), U(LCTL), END);
        }
        break;
    case 15: // emacs write buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(S), U(LCTL), END);
        }
        break;
    case 16: // emacs undo
        if (record->event.pressed) {
            return MACRO(D(LCTL), D(LSFT), T(MINS), U(LSFT), U(LCTL), END);
        }
        break;
    case 17: // emacs redo
        if (record->event.pressed) {
            return MACRO(D(LALT), D(LSFT), T(MINS), U(LSFT), U(LALT), END);
        }
        break;
    case 18: // emacs previous buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(LEFT), END);
        }
        break;
    case 19: // emacs next buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(RGHT), END);
        }
        break;
    case 20:
        if (record->event.pressed) {
            SEND_STRING("good night");
        }
        break;
    case 21: // email sig (I know, could be done in outlook, but outlook sucks)
        if (record->event.pressed) {
            return MACRO(T(M), T(A), T(N), T(Y), T(SPC),
                         T(T), T(H), T(A), T(N), T(K), T(S), T(ENT),
                         T(C), T(H), T(E), T(E), T(R), T(S), T(ENT),
                         T(A), T(L), T(B), T(E), T(R), T(T), T(ENT), END);
        }
        break;
    case 22: // { };
        if (record->event.pressed) {
            return MACRO(T(ENT), D(LSFT), T(LBRC), U(LSFT), T(ENT),
                         D(LSFT), T(RBRC), U(LSFT), T(SCLN), T(UP),
                         T(TAB), END);
        }
        break;
    case 23:
        if (record->event.pressed) {
            SEND_STRING("template");
        }
        break;
    case 24:
        if (record->event.pressed) {
            SEND_STRING("typename ");
        }
        break;
    case 25:
        if (record->event.pressed) {
            SEND_STRING("nullptr");
        }
        break;
    case 26:
        if (record->event.pressed) {
            SEND_STRING("bool");
        }
        break;
    case 27:
        if (record->event.pressed) {
            SEND_STRING("const");
        }
        break;
    case 28:
        if (record->event.pressed) {
            SEND_STRING(":-)");
        }
        break;
    case 29:
        if (record->event.pressed) {
            SEND_STRING(":-(");
        }
        break;
    case 30: // dazed
        if (record->event.pressed) {
            send_keystrokes(NK_DOWN, KC_LSFT, KC_8, KC_MINS, KC_8, NK_UP, KC_LSFT, KC_NO);
        }
        break;
    case 31: // decaf
        if (record->event.pressed) {
            send_keystrokes(NK_DOWN, KC_LSFT, KC_C, KC_9, KC_MINS, KC_0, NK_UP, KC_LSFT, KC_NO);
        }
        break;
    case 32:
        if (record->event.pressed) {
            SEND_STRING("emacs -nw ");
        }
        break;
    case 33:
        if (record->event.pressed) {
            SEND_STRING("less -iR ");
        }
        break;
    case 34:
        if (record->event.pressed) {
            SEND_STRING("explicit");
        }
        break;
    case 35:
        if (record->event.pressed) {
            SEND_STRING("virtual ");
        }
        break;
    case 36: // emacs font smaller
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(EQL), U(LCTL), END);
        }
        break;
    case 37:  // emacs font bigger
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), T(MINS), U(LCTL), END);
        }
        break;
    case 38:
        if (record->event.pressed) {
            SEND_STRING("auto");
        }
        break;
    case 39: // emacs indent region
        if (record->event.pressed) {
            return MACRO(D(LCTL), D(LALT), T(NONUS_BSLASH), U(LALT), U(LCTL), END);
        }
        break;
    case 40:  // emacs kill buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(K), END);
        }
        break;
    case 41:
        if (record->event.pressed) {
            SEND_STRING(";-)");
        }
        break;
    case 42:  // emacs delete window
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(0), END);
        }
        break;
    case 43:  // emacs select buffer
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(B), END);
        }
        break;
    case 44:  // emacs dired
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(D), END);
        }
        break;
    case 45:  // emacs C-x 2
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(2), END);
        }
    case 46:  // emacs C-x 3
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(3), END);
        }
        break;
    case 47:  // emacs C-x 5 2
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(5), T(2), END);
        }
        break;
    case 48:  // emacs C-x 5 0
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(5), T(0), END);
        }
        break;
    case 49:  // emacs C-x 1
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(1), END);
        }
    case 50:
        if (record->event.pressed) {
            SEND_STRING("good afternoon");
        }
        break;
    case 51:
        if (record->event.pressed) {
            SEND_STRING("o_o");
        }
        break;
    case 52:  // emacs C-x o
        if (record->event.pressed) {
            return MACRO(D(LCTL), T(X), U(LCTL), T(O), END);
        }
        break;
    case 53:  // VSCode Ctl + Shft + E
        if (record->event.pressed) {
            return MACRO(D(LCTL), D(LSFT), T(E), U(LSFT), U(LCTL), END);
        }
        break;
    case 54:  // VSCode Ctl + ` (or rather ' for icaclient)
        if (record->event.pressed) {
            send_keystrokes(NK_DOWN, KC_LCTL, KC_QUOT, NK_UP, KC_LCTL, KC_NO);
        }
        break;
    case 55:
        if (record->event.pressed) {
            SEND_STRING("constexpr ");
        }
        break;
    case 56:  // up 10
        if (record->event.pressed) {
            return MACRO(T(UP), T(UP), T(UP), T(UP), T(UP),
                         T(UP), T(UP), T(UP), T(UP), T(UP), END);
        }
        break;
    case 57:  // down 10
        if (record->event.pressed) {
            return MACRO(T(DOWN), T(DOWN), T(DOWN), T(DOWN), T(DOWN),
                         T(DOWN), T(DOWN), T(DOWN), T(DOWN), T(DOWN), END);
        }
        break;
    case 58:  // right 10
        if (record->event.pressed) {
            return MACRO(T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT),
                         T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT), END);
        }
        break;
    case 59:  // left 10
        if (record->event.pressed) {
            return MACRO(T(LEFT), T(LEFT), T(LEFT), T(LEFT), T(LEFT),
                         T(LEFT), T(LEFT), T(LEFT), T(LEFT), T(LEFT), END);
        }
        break;
    case 60:  // up 20
        if (record->event.pressed) {
            return MACRO(T(UP), T(UP), T(UP), T(UP), T(UP),
                         T(UP), T(UP), T(UP), T(UP), T(UP),
                         T(UP), T(UP), T(UP), T(UP), T(UP),
                         T(UP), T(UP), T(UP), T(UP), T(UP), END);
        }
        break;
    case 61:  // down 20
        if (record->event.pressed) {
            return MACRO(T(DOWN), T(DOWN), T(DOWN), T(DOWN), T(DOWN),
                         T(DOWN), T(DOWN), T(DOWN), T(DOWN), T(DOWN),
                         T(DOWN), T(DOWN), T(DOWN), T(DOWN), T(DOWN),
                         T(DOWN), T(DOWN), T(DOWN), T(DOWN), T(DOWN), END);
        }
        break;
    case 62:  // right 20
        if (record->event.pressed) {
            return MACRO(T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT),
                         T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT),
                         T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT),
                         T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT), T(RIGHT), END);
        }
        break;
    case 63:  // left 20
        if (record->event.pressed) {
            return MACRO(T(LEFT), T(LEFT), T(LEFT), T(LEFT), T(LEFT),
                         T(LEFT), T(LEFT), T(LEFT), T(LEFT), T(LEFT),
                         T(LEFT), T(LEFT), T(LEFT), T(LEFT), T(LEFT),
                         T(LEFT), T(LEFT), T(LEFT), T(LEFT), T(LEFT), END);
        }
        break;
    case 64:
        if (record->event.pressed) {
            SEND_STRING("static ");
        }
        break;
    case 65:
        if (record->event.pressed) {
            send_keystrokes(KC_SPC, NK_DOWN, KC_LSFT, KC_NONUS_BSLASH, NK_UP, KC_LSFT, KC_NO);
            SEND_STRING(" less -iR");
        }
        break;
    case 66:
        if (record->event.pressed) {
            SEND_STRING("[[nodiscard]] ");
        }
        break;
    case 67:
        if (record->event.pressed) {
            SEND_STRING("hello ");
        }
        break;
    case 68:
        if (record->event.pressed) {
            SEND_STRING("good evening");
        }
        break;
    case 69:
        if (record->event.pressed) {
            SEND_STRING("journalctl --user --pager-end ");
        }
        break;
    }
    return MACRO_NONE;
}

LEADER_EXTERNS();

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_TWO_KEYS(KC_G, KC_A) {
            SEND_STRING("git add .");
        }
        SEQ_THREE_KEYS(KC_G, KC_A, KC_U) {
            SEND_STRING("git add -u");
        }
        SEQ_TWO_KEYS(KC_G, KC_D) {
            SEND_STRING("git diff ");
        }
        SEQ_THREE_KEYS(KC_G, KC_D, KC_S) {
            SEND_STRING("git diff --staged");
        }
        SEQ_TWO_KEYS(KC_G, KC_L) {
            SEND_STRING("git log");
        }
        SEQ_THREE_KEYS(KC_G, KC_L, KC_O) {
            SEND_STRING("git log --oneline");
        }
        SEQ_TWO_KEYS(KC_G, KC_F) {
            SEND_STRING("git fetch");
        }
        SEQ_THREE_KEYS(KC_G, KC_F, KC_A) {
            SEND_STRING("git fetch --all");
        }
        SEQ_TWO_KEYS(KC_G, KC_B) {
            SEND_STRING("git branch");
        }
        SEQ_THREE_KEYS(KC_G, KC_B, KC_A) {
            SEND_STRING("git branch --all");
        }
        SEQ_THREE_KEYS(KC_G, KC_B, KC_C) {
            SEND_STRING("git branch --contains");
        }
        SEQ_FOUR_KEYS(KC_G, KC_B, KC_A, KC_C) {
            SEND_STRING("git branch --all --contains");
        }
        SEQ_TWO_KEYS(KC_G, KC_G) {
            SEND_STRING("git grep ");
        }
        SEQ_TWO_KEYS(KC_G, KC_M) {
            SEND_STRING("git merge");
        }
        SEQ_THREE_KEYS(KC_G, KC_M, KC_F) {
            SEND_STRING("git merge --ff-only upstream/");
        }
        SEQ_TWO_KEYS(KC_G, KC_O) {
            SEND_STRING("git checkout ");
        }
        SEQ_TWO_KEYS(KC_G, KC_P) {
            SEND_STRING("git pull");
        }
        SEQ_TWO_KEYS(KC_G, KC_U) {
            SEND_STRING("git push");
        }
        SEQ_THREE_KEYS(KC_G, KC_U, KC_F) {
            SEND_STRING("git push --force");
        }
        SEQ_THREE_KEYS(KC_G, KC_U, KC_S) {
            SEND_STRING("git push --set-upstream origin HEAD");
        }
        SEQ_TWO_KEYS(KC_G, KC_S) {
            SEND_STRING("git submodule ");
        }
        SEQ_THREE_KEYS(KC_G, KC_S, KC_S) {
            SEND_STRING("git submodule summary");
        }
        SEQ_THREE_KEYS(KC_G, KC_S, KC_U) {
            SEND_STRING("git submodule update --init --recursive");
        }
        SEQ_TWO_KEYS(KC_G, KC_C) {
            SEND_STRING("git commit -m ''");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_THREE_KEYS(KC_G, KC_C, KC_A) {
            SEND_STRING("git commit --amend");
        }
        SEQ_FOUR_KEYS(KC_G, KC_C, KC_A, KC_N) {
            SEND_STRING("git commit --amend --no-edit");
        }
        SEQ_THREE_KEYS(KC_G, KC_C, KC_I) {
            SEND_STRING("git ls-files ");
            send_keystrokes(NK_DOWN, KC_LSFT, KC_NONUS_BSLASH, NK_UP, KC_LSFT, KC_NO);
            SEND_STRING(" git check-ignore --stdin --verbose --non-match --no-index");
        }
        SEQ_TWO_KEYS(KC_G, KC_N) {
            SEND_STRING("git clean -dxf && git submodule foreach --recursive 'git clean -dxf'");
        }
        SEQ_TWO_KEYS(KC_C, KC_C) {
            SEND_STRING("const_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_TWO_KEYS(KC_C, KC_D) {
            SEND_STRING("dynamic_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_TWO_KEYS(KC_C, KC_R) {
            SEND_STRING("reinterpret_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }
        SEQ_TWO_KEYS(KC_C, KC_S) {
            SEND_STRING("static_cast<>");
            send_keystrokes(KC_LEFT, KC_NO);
        }

        SEQ_ONE_KEY(KC_S) {
            SEND_STRING("systemctl --user ");
        }
        SEQ_TWO_KEYS(KC_S, KC_S) {
            SEND_STRING("systemctl --user status ");
        }

        SEQ_TWO_KEYS(KC_A, KC_A) {
            SEND_STRING("alias g='grep --color=auto'");
            send_keystrokes(KC_ENT, KC_NO);
            SEND_STRING("alias l='ls -alF --color=auto'");
            send_keystrokes(KC_ENT, KC_NO);
        }
        SEQ_THREE_KEYS(KC_A, KC_A, KC_E) {
            SEND_STRING("alias g='grep --color=auto'");
            send_keystrokes(KC_ENT, KC_NO);
            SEND_STRING("alias l='ls -alF --color=auto'");
            send_keystrokes(KC_ENT, KC_NO);
            SEND_STRING("set -o emacs");
            send_keystrokes(KC_ENT, KC_NO);
            SEND_STRING("export HISTCONTROL=ignorespace");
            send_keystrokes(KC_ENT, KC_NO);
            SEND_STRING("unset LC_ALL");
            send_keystrokes(KC_ENT, KC_NO);
            SEND_STRING("unset LESS");
            send_keystrokes(KC_ENT, KC_NO);
        }
        SEQ_TWO_KEYS(KC_A, KC_G) {
            SEND_STRING("alias g='grep --color=auto'");
        }
        SEQ_TWO_KEYS(KC_A, KC_L) {
            SEND_STRING("alias l='ls -alF --color=auto'");
        }

        SEQ_TWO_KEYS(KC_D, KC_A) {
            SEND_STRING("gdb --args ");
        }
        SEQ_TWO_KEYS(KC_D, KC_P) {
            SEND_STRING("gdb --pid=");
        }

        SEQ_TWO_KEYS(KC_J, KC_B) {
            SEND_STRING("jj bookmark list ");
        }
        SEQ_THREE_KEYS(KC_J, KC_B, KC_A) {
            SEND_STRING("jj bookmark list --all-remotes ");
        }
        SEQ_TWO_KEYS(KC_J, KC_C) {
            SEND_STRING("jj bookmark create --revision ");
            send_keystrokes(NK_DOWN, KC_LSFT, KC_QUOT, NK_UP, KC_LSFT, KC_NO);
            SEND_STRING("- ");
        }
        SEQ_TWO_KEYS(KC_J, KC_D) {
            SEND_STRING("jj diff ");
        }
        SEQ_TWO_KEYS(KC_J, KC_F) {
            SEND_STRING("jj git fetch --all-remotes");
        }
        SEQ_TWO_KEYS(KC_J, KC_L) {
            SEND_STRING("jj log --revisions '::");
            send_keystrokes(NK_DOWN, KC_LSFT, KC_QUOT, NK_UP, KC_LSFT, KC_NO);
            SEND_STRING(" & bookmarks()'");
        }
        SEQ_TWO_KEYS(KC_J, KC_P) {
            SEND_STRING("jj git push --remote origin --bookmark ");
        }
        SEQ_TWO_KEYS(KC_J, KC_S) {
            SEND_STRING("jj status ");
        }

        SEQ_ONE_KEY(KC_P) {
            SEND_STRING("ps -L -O pid,ppid,lwp,user,args,comm,psr,pcpu,pri,nice,pmem,vsz,rss,etime,time,stat,wchan ");
        }

        SEQ_TWO_KEYS(KC_Q, KC_P) {
            SEND_STRING("podman run --interactive --tty --rm "
                "--volume=/home/albert/qmk_firmware:/qmk_firmware "
                "--volume=/dev:/dev qmk_cli");
        }
        SEQ_TWO_KEYS(KC_Q, KC_W) {
            SEND_STRING("https://github.com/zabereer/qmk_firmware/blob/albert/"
                        "layouts/community/ergodox/albert/keymap.c");
        }
        SEQ_TWO_KEYS(KC_Q, KC_C) {
            SEND_STRING("qmk compile --keyboard ergodox_ez --keymap albert");
        }
        SEQ_TWO_KEYS(KC_Q, KC_F) {
            SEND_STRING("qmk flash --keyboard ergodox_ez --keymap albert");
        }
    }
}
