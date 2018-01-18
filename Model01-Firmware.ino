// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

#include "Kaleidoscope-SpaceCadet.h"

#include "Kaleidoscope-LEDEffect-DigitalRain.h"



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { QWERTY, NUMPAD, FUNCTION }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

const Key keymaps[][ROWS][COLS] PROGMEM = {

  [QWERTY] = KEYMAP_STACKED
  (Key_Escape,                Key_1, Key_2, Key_3, Key_4, Key_5, Key_LeftBracket,
   Key_Backtick,              Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_Backslash,             Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_NonUsBackslashAndPipe, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_LeftAlt,
   Key_LeftGui, Key_Backspace, Key_LeftControl, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   Key_RightBracket, Key_6, Key_7, Key_8,     Key_9,         Key_0,         Key_Delete,
   Key_Enter,        Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                     Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_RightAlt,     Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_RightControl, Key_Spacebar, Key_LeftAlt,
   ShiftToLayer(FUNCTION)),

  [NUMPAD] =  KEYMAP_STACKED
  (___,  ___,           Key_Clear,       Key_KeypadDivide,   Key_KeypadMultiply, Key_KeypadEquals,   ___,
   ___,  ___,           Key_Keypad7,     Key_Keypad8,        Key_Keypad9,        Key_KeypadSubtract, ___,
   ___,  Key_Backspace, Key_Keypad4,     Key_Keypad5,        Key_Keypad6,        Key_KeypadAdd,
   ___,  ___,           Key_Keypad1,     Key_Keypad2,        Key_Keypad3,        Key_KeypadEnter,    ___,
   Key_Keypad0, Key_KeypadDot, ___, ___,
   ___,

   ___,  ___, ___, ___, ___, ___, ___,
   ___,  ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___,
   ___,  ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___, Key_F1,          Key_F2,                     Key_F3,                   Key_F4,                   Key_F5, Key_LEDEffectNext,
   ___, ___,             Consumer_ScanPreviousTrack, Consumer_PlaySlashPause,  Consumer_ScanNextTrack,   ___,    ___,
   ___, ___,             Key_Mute,                   Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,
   ___, Key_PrintScreen, Key_Insert,                 Key_CapsLock,              ___,                     ___,    ___,
   ___, ___, ___, ___,
   ___,

   ___,               Key_F6,        Key_F7,        Key_F8,      Key_F9,         Key_F10, Key_F11,
   ___,               ___,           ___,           ___,         ___,            ___,     Key_F12,
                      Key_LeftArrow, Key_DownArrow, Key_UpArrow, Key_RightArrow, ___,     ___,
   Key_PcApplication, Key_Home,      Key_PageDown,  Key_PageUp,  Key_End,        ___,     LockLayer(NUMPAD),
   ___, ___, ___, ___,
   ___)
};

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.
static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(

    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // Yeah digital rain
    &LEDDigitalRainEffect,

    // These static effects turn your keyboard's LEDs a variety of colors
    &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,

    // The rainbow effect changes the color of all of the keyboard's keys at the same time
    // running through all the colors of the rainbow.
    &LEDRainbowEffect,

    // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
    // and slowly moves the rainbow across your keyboard
    &LEDRainbowWaveEffect,

    // The breathe effect slowly pulses all of the LEDs on your keyboard
    &LEDBreatheEffect,

    // The numpad plugin is responsible for lighting up the 'numpad' mode
    // with a custom LED effect
    &NumPad,

    // The HostPowerManagement plugin enables waking up the host from suspend,
    // and allows us to turn LEDs off when it goes to sleep.
    &HostPowerManagement,

    &SpaceCadet
  );

  //Set the keymap with a 250ms timeout per-key
  //Setting is {KeyThatWasPressed, AlternativeKeyToSend, TimeoutInMS}
  //Note: must end with the SPACECADET_MAP_END delimiter
  static kaleidoscope::SpaceCadet::KeyBinding spacecadetmap[] = {
    {Key_LeftShift, Key_LeftBracket, 250}
    , {Key_RightShift, Key_RightBracket, 250}
    , {Key_LeftAlt, Key_LeftCurlyBracket, 250}
    , {Key_RightAlt, Key_RightCurlyBracket, 250}
    , {Key_LeftControl, Key_LeftParen, 250}
    , {Key_RightControl, Key_RightParen, 250}
    , SPACECADET_MAP_END
  };

  SpaceCadet.map = spacecadetmap;

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  LEDDigitalRainEffect.DROP_TICKS = 22;
  LEDDigitalRainEffect.NEW_DROP_PROBABILITY = 15;

  // We want the keyboard to be able to wake the host up from suspend.
  HostPowerManagement.enableWakeup();

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
