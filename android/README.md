# Spin & Win Android port

The Android port can now launch and play Spin & Win using the reconstructed
Win32 runtime and SDL2. This is a working, playable port, although some features
still need fixes and device testing.

## Current status

- The Android launcher imports the extracted game folder through Android's
  folder picker and copies it into app-private storage.
- The launcher checks for `SpinWin.exe`, `Graphics`, and `Audio` before
  enabling **PLAY SPIN & WIN**.
- **PLAY SPIN & WIN** starts the SDL Android activity with the imported game
  folder.
- SDL 2.30.11 is built from the official source and linked into the native JNI
  library. SDL's Android Java glue is included from the same pinned release.
- The native entry point maps the imported folder as the guest C: drive,
  initializes the Win32 HLE host, opens the game display, loads `SpinWin.exe`
  through the permissive PE/import loader, and runs the reconstructed game code.
- **TEST SDL2 GRAPHICS + TOUCH** remains available as a separate graphics and
  touch diagnostic. Its animated wheel-like graphic is only a test; it is not
  the game itself.
- The game is playable on Android, but keyboard entry, dialog interaction, and
  sound still have known problems.

## Known issues / TODO

1. **Android keyboard does not appear reliably** — when the game asks the
   player to enter a name for a new high score, the on-screen keyboard does not
   appear or accept input as expected.
2. **Game dialogs respond unreliably** — dialogs such as the Exit confirmation
   do not always respond correctly to one click; sometimes two quick clicks
   are needed.
3. **Game sounds do not work correctly** — game audio is not currently
   functioning as expected in the Android port.

The hold-to-type and double-tap Enter touch shortcuts were experiments while
investigating the keyboard problem; they are not separate bugs.

The full-screen white borders were fixed and are not an open issue.

## Next steps

1. Fix Android keyboard display and text entry, including the high-score name
   prompt.
2. Fix single-click handling for game dialogs.
3. Implement and verify the audio path used by Spin & Win.
4. Retest gameplay, pause/resume, screen sizing, save behavior, and stability
   on physical Android devices.
5. Produce and test a release APK after the remaining issues are resolved.

## Build

Open this directory as an Android Gradle project, or run:

```sh
gradle :app:assembleDebug
```

CMake uses FetchContent to clone the official SDL repository at the pinned
`release-2.30.11` tag. The first native build therefore needs network access.

See [PORTING_PLAN.md](PORTING_PLAN.md) for the architecture and progress notes.
The SDL2 license is included in [SDL-LICENSE.txt](SDL-LICENSE.txt).
