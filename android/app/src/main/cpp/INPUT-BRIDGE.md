# Android input bridge

`android_input_bridge.c` is the planned SDL2-to-Win32 input adapter for the
Spin & Win host.

It converts the primary SDL finger into the input API already exposed by
`runtime/win32hle/win32hle.h`:

- finger down -> cursor position, WM_MOUSEMOVE, WM_LBUTTONDOWN
- finger motion -> cursor position and WM_MOUSEMOVE
- finger up -> cursor position and WM_LBUTTONUP

Coordinates are converted from SDL's normalized touch range to the virtual
game display dimensions passed by the caller. Additional simultaneous fingers
are ignored, which gives the game one predictable mouse pointer.

## Integration status

This source is a prepared adapter, **not yet part of the APK build**. It can be
added to the native target once the Win32 HLE runtime has been compiled into
the Android library. The existing SDL test crosshair only proves touch
recognition; it does not yet call this bridge or control the original game.
