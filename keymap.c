/* Copyright 2020 Duckle, 2021 Jesús Vallejo
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
#include "analog.h"
#include "qmk_midi.h"

/*
This keymap works with midi2vol: linux version  https://github.com/jesusvallejo/Midi2Vol-Linux  
and windows version https://github.com/jesusvallejo/Midi2Vol

Enables the user to change the volume on the host computer if running midi2vol software.

Example to extend usability is provided check VLC in: enum custom_keycodes {} and bool process_record_user(uint16_t keycode, keyrecord_t *record) {}
Remember to give allways the new volume control a hex value not used by other volume control, 
and add it to the midi2vol software.
Check respective midi2vol readme on how to do so.In linux change config.json,in windows you can use configuration option.

A compiled version of this keymap is provided in here: https://github.com/jesusvallejo/nanokeymaps/

*/

uint8_t midi2vol = 0x3E;

// Defines names for use in layer keycodes and the keymap

#define _MEDIA 0 // Controls Pause, Mute , Forward ...

#define _NAV 1 // Nav arrows, Enter, Space

#define _VOLUME 2 // Changes midi2vol int to interface with midi2vol program: Chrome Volume, General Volume

#define _DISCORD 3 // FXX unsused keys to interface with Discord: Mute , Silence

#define _LIGHTS 4 // Edits underglow and retroilumination

#define _EDIT 5 // Cut, Copy ,Paste

#define _RESET 6 // layer to set nano in bootloader mode

#define _TOOGLE 7 // momentary layer to switch between layers



// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { // In order to add more volume controls, add here a custom keycode, ex: VLC
    DEFAULT,
    SPOTIFY,
    DISCORD,
    CHROME
    //,VLC 
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_MEDIA] = LAYOUT(
        MO(_TOOGLE),
        KC_MPLY, KC_MNXT,  KC_COPY,
        KC_MUTE,  KC_MPRV, KC_PASTE, KC_ENTER
    ),
        [_NAV] = LAYOUT(
        MO(_TOOGLE),
        KC_SPC, KC_UP, KC_BSPACE,
        KC_RIGHT, KC_DOWN, KC_LEFT, KC_ENTER      
    ),
    [_VOLUME] = LAYOUT(
        MO(_TOOGLE),
        SPOTIFY, DISCORD, CHROME,
        KC_NO, KC_NO, KC_NO, DEFAULT
    ),
    [_DISCORD] = LAYOUT(
        MO(_TOOGLE),
        KC_F18, KC_F19, KC_F20,
        KC_F21, KC_F22, KC_F23, KC_F24
    ),
    [_LIGHTS] = LAYOUT(
        MO(_TOOGLE),
        RGB_TOG, RGB_MOD, RGB_VAI,
        BL_SAI, BL_BRTG, BL_STEP, KC_LSFT
    ),
    [_EDIT] = LAYOUT(
        MO(_TOOGLE),
        KC_MENU, KC_CUT, KC_COPY,
        KC_FIND, KC_UNDO, KC_PASTE, KC_MPLY
    ),
    [_RESET] = LAYOUT(
        MO(_TOOGLE),
        KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, RESET 
    ),
    [_TOOGLE] = LAYOUT(
        MO(_TOOGLE),
        TO(_MEDIA),    TO(_NAV),    TO(_VOLUME),
        TO(_DISCORD),    TO(_LIGHTS),    TO(_EDIT),    TO(_RESET)
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) { // In order to add more volume controls, add here code to detect custom keycode, ex: VLC
    switch (keycode) {
        case DEFAULT:
            if (record->event.pressed) {
                // when keycode DEFAULT is pressed
                midi2vol= 0x3E;
            } else {
                // when keycode DEFAULT is released
            }
            break;
        case SPOTIFY:
            if (record->event.pressed) {
                // when keycode SPOTIFY is pressed
                midi2vol= 0x3F;
            } else {
                
                // when keycode SPOTIFY is released
            }
            break;
        case DISCORD:
            if (record->event.pressed) {
                // when keycode DISCORD is pressed
                midi2vol= 0x40;
            } else {
                
                // when keycode DISCORD is released
            }
            break;
        case CHROME:
            if (record->event.pressed) {
                // when keycode CHROME is pressed
                midi2vol= 0x41;
            } else {
                
                // when keycode CHROME is released
            }
            break;
        /*
        case CHROME:
            if (record->event.pressed) {
                // when keycode VLC is pressed
                midi2vol= 0x42;
            } else {
                
                // when keycode VLC is released
            }
            break;
        */
    }
    return true;
}

uint8_t divisor = 0;


void slider(void) {
    if (divisor++) { // only run the slider function 1/256 times it's called
        return;
    }

    midi_send_cc(&midi_device, 2, midi2vol, 0x7F - (analogReadPin(SLIDER_PIN) >> 3));
}

void matrix_scan_user(void) {
    slider();
}