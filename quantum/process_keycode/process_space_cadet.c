/* Copyright 2019 Jack Humbert
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
#include "process_space_cadet.h"

#ifndef TAPPING_TERM
  #define TAPPING_TERM 200
#endif

// ********** OBSOLETE DEFINES, STOP USING! (pls?) **********
// Shift / paren setup
#ifndef LSPO_KEY
  #define LSPO_KEY KC_9
#endif
#ifndef RSPC_KEY
  #define RSPC_KEY KC_0
#endif

// Shift / Enter setup
#ifndef SFTENT_KEY
  #define SFTENT_KEY KC_ENT
#endif

#ifdef DISABLE_SPACE_CADET_MODIFIER
  #ifndef LSPO_MOD
    #define LSPO_MOD KC_TRNS
  #endif
  #ifndef RSPC_MOD
    #define RSPC_MOD KC_TRNS
  #endif
#else
  #ifndef LSPO_MOD
    #define LSPO_MOD KC_LSFT
  #endif
  #ifndef RSPC_MOD
    #define RSPC_MOD KC_RSFT
  #endif
#endif
// **********************************************************

// Shift / paren setup
#ifndef LSPO_KEYS
  #define LSPO_KEYS KC_LSFT, LSPO_MOD, LSPO_KEY
#endif
#ifndef RSPC_KEYS
  #define RSPC_KEYS KC_RSFT, RSPC_MOD, RSPC_KEY
#endif

// Control / paren setup
#ifndef LCPO_KEYS
  #define LCPO_KEYS KC_LCTL, KC_LCTL, KC_9
#endif
#ifndef RCPO_KEYS
  #define RCPO_KEYS KC_RCTL, KC_RCTL, KC_0
#endif

// Alt / paren setup
#ifndef LAPO_KEYS
  #define LAPO_KEYS KC_LALT, KC_LALT, KC_9
#endif
#ifndef RAPO_KEYS
  #define RAPO_KEYS KC_RALT, KC_RALT, KC_0
#endif

// Shift / Enter setup
#ifndef SFTENT_KEYS
  #define SFTENT_KEYS KC_RSFT, KC_TRNS, SFTENT_KEY
#endif

static uint8_t sc_last = 0;
static uint16_t sc_timer = 0;

void perform_space_cadet(keyrecord_t *record, uint8_t normalMod, uint8_t tapMod, uint8_t keycode) {
  if (record->event.pressed) {
    sc_last = normalMod;
    sc_timer = timer_read ();
    if (IS_MOD(normalMod)) {
      register_mods(MOD_BIT(normalMod));
    }
  }
  else {
    if (IS_MOD(normalMod)) {
      unregister_mods(MOD_BIT(normalMod));
    }

    if (sc_last == normalMod && timer_elapsed(sc_timer) < TAPPING_TERM) {
      if (IS_MOD(tapMod)) {
        register_mods(MOD_BIT(tapMod));
      }
      tap_code(keycode);
      if (IS_MOD(tapMod)) {
        unregister_mods(MOD_BIT(tapMod));
      }
    }
  }
}

bool process_space_cadet(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_LSPO: {
      perform_space_cadet(record, LSPO_KEYS);
      return false;
    }
    case KC_RSPC: {
      perform_space_cadet(record, RSPC_KEYS);
      return false;
    }
    case KC_LCPO: {
      perform_space_cadet(record, LCPO_KEYS);
      return false;
    }
    case KC_RCPC: {
      perform_space_cadet(record, RCPO_KEYS);
      return false;
    }
    case KC_LAPO: {
      perform_space_cadet(record, LAPO_KEYS);
      return false;
    }
    case KC_RAPC: {
      perform_space_cadet(record, RAPO_KEYS);
      return false;
    }
    case KC_SFTENT: {
      perform_space_cadet(record, SFTENT_KEYS);
      return false;
    }
    default: {
      sc_last = 0;
      break;
    }
  }
  return true;
}
