# Spin & Win Android port

This is an Android launcher and an in-progress native port. It is **not yet a
playable build of Spin & Win**.

## Current status

- The launcher imports the extracted game folder through Android's folder picker.
- SDL 2.30.11 is built from the official source and linked into the native JNI
  library for the configured Android ABIs.
- SDL's Android Java glue is included from the same pinned SDL release.
- **TEST SDL2 GRAPHICS + TOUCH** opens a separate SDL activity. The native test
  draws an animated wheel-like graphic and displays a touch crosshair. This is
  a graphics/input plumbing test, not the original game.
- **PLAY SPIN & WIN** remains disabled until the Win32 guest runtime, reconstructed
  SpinWin code, graphics, input and audio are integrated and tested.

## Build

Open this directory as an Android Gradle project, or run:

```sh
gradle :app:assembleDebug
```

CMake uses FetchContent to clone the official SDL repository at the pinned
`release-2.30.11` tag. The first native build therefore needs network access.

## Next engineering steps

1. Verify the SDL test activity on a physical ARM64 Android device.
2. Port the portable pcrecomp Win32 HLE runtime to Android/SDL.
3. Integrate the SpinWin lifted C output, guest memory, PE loader and imports.
4. Implement the FMOD compatibility layer and touch-to-mouse input.
5. Enable Play only after the original game reaches a real first frame on Android.

See [PORTING_PLAN.md](PORTING_PLAN.md) for the architecture and acceptance tests.
The SDL2 license is included in [SDL-LICENSE.txt](SDL-LICENSE.txt).
