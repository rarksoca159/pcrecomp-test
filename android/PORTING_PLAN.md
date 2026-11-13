# Spin & Win Android port plan

## Current state

The Android port now launches and plays Spin & Win through the reconstructed
Win32 HLE runtime and SDL2. The launcher imports the original game folder into
app-private storage, checks that the expected game files exist, and enables
**PLAY SPIN & WIN** when they are present.

The SDL Android activity passes the imported folder to the native entry point.
The native host maps that folder as the guest C: drive, initializes the Win32
HLE runtime, opens the SDL game display, loads `SpinWin.exe` with the
permissive PE/import loader, and runs the reconstructed C output.

The separate **TEST SDL2 GRAPHICS + TOUCH** activity is still a diagnostic
screen only. It is not the game renderer or a gameplay mode.

The port is playable, but keyboard entry, dialog interaction, and audio remain
known issues. See [README.md](README.md).

## Implemented architecture

- Android launcher and game-folder import using the Storage Access Framework.
- SDL2 2.30.11 Android integration and SDL Java activity glue.
- JNI/native SDL entry point and imported-game-folder argument.
- Guest C: drive mapping to the imported game directory.
- Reconstructed SpinWin lifted C output and dispatch integration.
- Win32 HLE host initialization, PE loading, permissive import binding, and
  execution of the guest game.
- SDL display and Android touch/input path sufficient to play the game.

## Remaining milestones

1. **Keyboard and text input**
   - Make Android's on-screen keyboard appear at the correct time.
   - Deliver committed text to the game's high-score name-entry control.
   - Verify editing keys and Enter behavior.

2. **Window/dialog input**
   - Make buttons and dialogs respond correctly to a single tap.
   - Check event dispatch, mouse button transitions, and dialog lifetime.

3. **Audio**
   - Implement or complete the FMOD compatibility path used by Spin & Win,
     using SDL2 audio where appropriate.
   - Verify music and sound effects independently.

4. **Stability and release**
   - Retest asset paths, save/config writes, pause/resume, and activity
     recreation.
   - Verify display sizing and touch behavior on physical Android devices.
   - Produce and test a release APK after the known issues are fixed.

## Technical notes

The target executable is a 32-bit x86 Windows PE. Its lifted C runs as guest
code through the pcrecomp (https://github.com/sp00nznet/pcrecomp) runtime; it is not compiled as native ARM game code.
The Android host and SDL2 provide the platform integration.

The reconstructed C is machine-code lifting, not original developer source.
Some imported Windows/DLL behavior is provided by HLE shims or permissive
fallback stubs, so additional API compatibility work may be needed if new
gameplay paths expose unresolved behavior.
