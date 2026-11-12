# Spin & Win Android port plan

## Current state

The Android app is a launcher/import scaffold. It can select the extracted game
folder and copy it into app-private storage. It does not execute `SpinWin.exe`;
the Play button must remain disabled until the native engine can boot safely.

The target is a 32-bit x86 Windows GUI executable. Its lifted C is not a
standalone game: it needs the pcrecomp 32-bit guest CPU/memory/PE-loader runtime
and implementations for the Windows APIs it imports.

## Recommended architecture

Reuse pcrecomp's `runtime/win32hle` where practical. It already contains a
software implementation of Win32 services including PE loading, guest memory,
USER32 message handling, GDI, DirectDraw surfaces, keyboard/mouse input and
DirectSound-style audio. Its display and audio backend currently uses SDL2 on
desktop POSIX systems; this is not yet an Android backend.

For Android, build an SDL2 Android application/native activity with the NDK,
then adapt the host integration and filesystem paths to Android's app-private
game directory. Keep the guest x86 address space and lifted code separate from
the ARM64/ARM Android host CPU; do not try to compile the x86 guest instructions
as native ARM code.

## Milestones

1. **Runtime build on Android**
   - Add SDL2's Android build to the Gradle/NDK project.
   - Compile the portable parts of `runtime/win32hle` and its dependencies.
   - Resolve POSIX-only calls and Android linker/build differences.
   - Show a native SDL2 test frame and accept touch input before loading the game.

2. **Game executable loading**
   - Bring the SpinWin lifted C output into the build as generated source (not
     the original EXE).
   - Integrate the matching recomp32 guest runtime, PE image layout and import
     table for this exact executable.
   - Map the imported game folder as the guest's virtual C: drive and verify
     that the PE entry point can be reached.

3. **Graphics and input**
   - Connect the game's DirectDraw calls to the software surface backend.
   - Present frames through SDL2 on Android in landscape orientation.
   - Map touch input to the mouse actions the game expects; add back/navigation
     handling without stealing in-game input.

4. **Audio**
   - Implement the FMOD API surface actually imported/called by SpinWin, or
     replace it with a compatible SDL2 audio shim.
   - Verify music and sound effects independently.

5. **Stability and release**
   - Add tests for asset paths, save/config writes, pause/resume and activity
     recreation.
   - Enable Play only after a real boot test passes on ARM64 Android.
   - Produce and test a signed release APK.

## Known risks / work still required

- `win32hle` is documented as a Linux/macOS SDL2 host today; Android support
  must be implemented and tested, not assumed.
- Its existing audio shims include DirectSound and Miles-related support, but
  the Spin & Win executable uses FMOD; FMOD compatibility is a separate task.
- The reconstructed C is machine-code lifting, not original source. It must be
  compiled with the exact generated headers, dispatch table, memory image and
  import stubs for this game.
- The current repository's Android module contains only a JNI placeholder; it
  does not yet include the game's lifted C output or a runnable game host.

## First acceptance test

A debug APK on an ARM64 Android device starts an SDL2 screen, loads the
SpinWin PE image through the guest loader, resolves all required imports (or
reports the first unresolved import clearly), and displays the game's first
frame. Until that test passes, the launcher must describe the engine as in
development and Play must stay disabled.
