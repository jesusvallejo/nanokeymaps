# nanokeymaps
Nano. slider personal keymap

This keymap works with midi2vol: linux version  https://github.com/jesusvallejo/Midi2Vol-Linux  
and windows version https://github.com/jesusvallejo/Midi2Vol

Enables the user to change the volume on the host computer if running midi2vol software.

Example to extend usability is provided check VLC in: ```enum custom_keycodes {}``` and ```bool process_record_user(uint16_t keycode, keyrecord_t *record) {}```
Remember to give allways the new volume control a hex value not used by other volume control, and add it to the midi2vol software.
Check respective midi2vol readme on how to do so:
  - In linux change config.json.
  - In windows you can use configuration option(config.json is available under \user\appdata\midi2vol).

A compiled version of this keymap is provided in here: https://github.com/jesusvallejo/nanokeymaps/
