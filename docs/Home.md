# Quantum Mechanical Keyboard Firmware

You have found the QMK Firmware documentation site. This is a keyboard firmware based on the [tmk\_keyboard firmware](http://github.com/tmk/tmk_keyboard) \([view differences](/Differences-from-TMK.md)\) with some useful features for Atmel AVR controllers, and more specifically, the [OLKB product line](http://olkb.com), the [ErgoDox EZ](http://www.ergodox-ez.com) keyboard, and the [Clueboard product line](http://clueboard.co/). It has also been ported to ARM chips using ChibiOS. You can use it to power your own hand-wired or custom keyboard PCB.

# Getting started

Before you are able to compile, you'll need to install an environment for AVR or ARM development. You'll find the instructions for any OS below. If you find another/better way to set things up from scratch, please consider [making a pull request](https://github.com/qmk/qmk_firmware/pulls) with your changes!

* [Build Environment Setup](/Build-Environment-Setup.md)
* [QMK Overview](/QMK-Overview.md)

# Configuring QMK Firmware

The QMK Firmware can be configured via the `keymaps` array data. For simply generating a [basic keycode](/Keycodes.md), you add it as an element of your `keymaps` array data. For more complicated actions, there are more advanced keycodes that are organized carefully to represent common operations, some of which can be found on the [Key Functions](/Key-Functions.md) page.

For more details of the `keymaps` array, see [Keymap Overview](/Keymap.md) page.

## Space Cadet Shift: The future, built in

Steve Losh [described](http://stevelosh.com/blog/2012/10/a-modern-space-cadet/) the Space Cadet Shift quite well. Essentially, you hit the left Shift on its own, and you get an opening parenthesis; hit the right Shift on its own, and you get the closing one. When hit with other keys, the Shift key keeps working as it always does. Yes, it's as cool as it sounds. Head on over to the [Space Cadet Shift](/Space-Cadet-Shift.md) page to read about it.

## The Leader key: A new kind of modifier

Most modifiers have to be held or toggled. But what if you had a key that indicated the start of a sequence? You could press that key and then rapidly press 1-3 more keys to trigger a macro, or enter a special layer, or anything else you might want to do. To learn more about it check out the [Leader Key](/Leader-Key.md) page.

## Tap Dance: A single key can do 3, 5, or 100 different things

Hit the semicolon key once, send a semicolon. Hit it twice, rapidly -- send a colon. Hit it three times, and your keyboard's LEDs do a wild dance. That's just one example of what Tap Dance can do. Read more about it on the [Tap Dance](/Tap-Dance.md) page.

## Temporarily setting the default layer

`DF(layer)` - sets default layer to _layer_. The default layer is the one at the "bottom" of the layer stack - the ultimate fallback layer. This currently does not persist over power loss. When you plug the keyboard back in, layer 0 will always be the default. It is theoretically possible to work around that, but that's not what `DF` does.

## Macro shortcuts: Send a whole string when pressing just one key

How would you like a single keypress to send a whole word, sentence, paragraph, or even document? Head on over to the [Macros](/Macros.md) page to read up on all aspects of Simple and Dynamic Macros.

## Additional keycode aliases for software-implemented layouts \(Colemak, Dvorak, etc\)

Everything is assuming you're in Qwerty \(in software\) by default, but there is built-in support for using a Colemak or Dvorak layout by including this at the top of your keymap:

```
#include <keymap_colemak.h>
```

If you use Dvorak, use `keymap_dvorak.h` instead of `keymap_colemak.h` for this line. After including this line, you will get access to:

* `CM_*` for all of the Colemak-equivalent characters
* `DV_*` for all of the Dvorak-equivalent characters

These implementations assume you're using Colemak or Dvorak on your OS, not on your keyboard - this is referred to as a software-implemented layout. If your computer is in Qwerty and your keymap is in Colemak or Dvorak, this is referred to as a firmware-implemented layout, and you won't need these features.

To give an example, if you're using software-implemented Colemak, and want to get an `F`, you would use `CM_F`. Using `KC_F` under these same circumstances would result in `T`.

## Backlight Breathing

In order to enable backlight breathing, the following line must be added to your config.h file.

```
#define BACKLIGHT_BREATHING
```

The following function calls are used to control the breathing effect.

* `breathing_enable()` - Enable the free-running breathing effect.
* `breathing_disable()` - Disable the free-running breathing effect immediately.
* `breathing_self_disable()` - Disable the free-running breathing effect after the current effect ends.
* `breathing_toggle()` - Toggle the free-running breathing effect.
* `breathing_defaults()` - Reset the speed and brightness settings of the breathing effect.

The following function calls are used to control the maximum brightness of the breathing effect.

* `breathing_intensity_set(value)` - Set the brightness of the breathing effect when it is at its max value.
* `breathing_intensity_default()` - Reset the brightness of the breathing effect to the default value based on the current backlight intensity.

The following function calls are used to control the cycling speed of the breathing effect.

* `breathing_speed_set(value)` - Set the speed of the breathing effect - how fast it cycles.
* `breathing_speed_inc(value)` - Increase the speed of the breathing effect by a fixed value.
* `breathing_speed_dec(value)` - Decrease the speed of the breathing effect by a fixed value.
* `breathing_speed_default()` - Reset the speed of the breathing effect to the default value.

The following example shows how to enable the backlight breathing effect when the FUNCTION layer macro button is pressed:

```
case MACRO_FUNCTION:
    if (record->event.pressed)
    {
        breathing_speed_set(3);
        breathing_enable();
        layer_on(LAYER_FUNCTION);
    }
    else
    {
        breathing_speed_set(1);
        breathing_self_disable();
        layer_off(LAYER_FUNCTION);
    }
    break;
```

The following example shows how to pulse the backlight on-off-on when the RAISED layer macro button is pressed:

```
case MACRO_RAISED:
  if (record->event.pressed)
  {
    layer_on(LAYER_RAISED);
    breathing_speed_set(2);
    breathing_pulse();
    update_tri_layer(LAYER_LOWER, LAYER_RAISED, LAYER_ADJUST);
  }
  else
  {
    layer_off(LAYER_RAISED);
    update_tri_layer(LAYER_LOWER, LAYER_RAISED, LAYER_ADJUST);
  }
  break;
```

## Other firmware shortcut keycodes

* `RESET` - puts the MCU in DFU mode for flashing new firmware \(with `make dfu`\)
* `DEBUG` - the firmware into debug mode - you'll need hid\_listen to see things
* `BL_ON` - turns the backlight on
* `BL_OFF` - turns the backlight off
* `BL_<n>` - sets the backlight to level _n_
* `BL_INC` - increments the backlight level by one
* `BL_DEC` - decrements the backlight level by one
* `BL_TOGG` - toggles the backlight
* `BL_STEP` - steps through the backlight levels

Enable the backlight from the Makefile.

# Custom Quantum functions

All of these functions are available in the `*_kb()` or `*_user()` variety. `kb` ones should only be used in the `<keyboard>/<keyboard>.c` file, and `user` ones should only be used in the `keymap.c`. The keyboard ones call the user ones - it's necessary to keep these calls to allow the keymap functions to work correctly.

## `void matrix_init_*(void)`

This function gets called when the matrix is initiated, and can contain start-up code for your keyboard/keymap.

## `void matrix_scan_*(void)`

This function gets called at every matrix scan, which is basically as often as the MCU can handle. Be careful what you put here, as it will get run a lot.

## `bool process_record_*(uint16_t keycode, keyrecord_t *record)`

This function gets called on every keypress/release, and is where you can define custom functionality. The return value is whether or not QMK should continue processing the keycode - returning `false` stops the execution.

The `keycode` variable is whatever is defined in your keymap, eg `MO(1)`, `KC_L`, etc. and can be switch-cased to execute code whenever a particular code is pressed.

The `record` variable contains infomation about the actual press:

```
keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}
```

The conditional `if (record->event.pressed)` can tell if the key is being pressed or released, and you can execute code based on that.

## `void led_set_*(uint8_t usb_led)`

This gets called whenever there is a state change on your host LEDs \(eg caps lock, scroll lock, etc\). The LEDs are defined as:

```
#define USB_LED_NUM_LOCK                0
#define USB_LED_CAPS_LOCK               1
#define USB_LED_SCROLL_LOCK             2
#define USB_LED_COMPOSE                 3
#define USB_LED_KANA                    4
```

and can be tested against the `usb_led` with a conditional like `if (usb_led & (1<<USB_LED_CAPS_LOCK))` - if this is true, you can turn your LED on, otherwise turn it off.

