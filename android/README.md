# Spin & Win Android port

This is an Android launcher and an in-progress native port. It is **not yet a
playable build of Spin & Win**.

## Current status

- The launcher can import the extracted game folder through Android's folder picker.
- The Android NDK build fetches the official SDL 2.30.11 source and links its
  static library into the app's native JNI library for both configured Android
  ABIs.
- The app reports the linked SDL2 version at startup. This confirms native
  SDL2 is present in the APK; it does not yet mean an SDL display or the game
  engine is running.
- The Play button remains disabled until the Win32 guest runtime, reconstructed
  SpinWin code, graphics, input and audio are integrated and tested.

## Build

Open this directory as an Android Gradle project, or run:

```sh
gradle :app:assembleDebug
```

CMake uses FetchContent to clone the official SDL repository at the pinned
`release-2.30.11` tag. The first native build therefore needs network access.

## Next engineering steps

1. Add SDL's Android Java activity glue and start a real SDL window/surface.
2. Port the portable pcrecomp Win32 HLE runtime to Android/SDL.
3. Integrate the SpinWin lifted C output, guest memory, PE loader and imports.
4. Implement the FMOD compatibility layer and touch-to-mouse input.
5. Enable Play only after the game reaches a real first frame on an ARM64 device.

See [PORTING_PLAN.md](PORTING_PLAN.md) for the architecture and acceptance tests.
