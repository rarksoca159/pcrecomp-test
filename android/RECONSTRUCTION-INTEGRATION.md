# Spin & Win reconstructed-code integration assessment

This assessment was made from the supplied `SpinWin_reconstructed_C_source.zip`
and the current `runtime/win32hle` implementation.

## Lifted program

- PE: 32-bit x86 Windows GUI executable, preferred image base `0x00400000`.
- Entry point: `0x00415C64`.
- Reconstructed functions: 879.
- Generated files: `c/recomp_0000.c`, `c/recomp_dispatch.c`,
  `c/recomp_funcs.h`, `functions.json`, `pe-analysis.json`, and
  `import-stubs.c`.
- The repository already supplies `runtime/recomp32/recomp_types.h`, which
  is the core register/memory/CPU model required by the generated C.

The generated C is lifted machine code, not recovered original source code.
It must run inside the matching pcrecomp guest-memory and Win32 HLE runtime.

## Imported Windows APIs

The PE import table contains 120 imports across seven DLLs:

| DLL | Imports |
|---|---:|
| KERNEL32.dll | 56 |
| USER32.dll | 37 |
| FMOD.dll | 14 |
| GDI32.dll | 9 |
| WINMM.dll | 2 |
| SHELL32.dll | 1 |
| DDRAW.dll | 1 |

The existing runtime has substantial implementations for kernel32, user32,
gdi32, winmm and DirectDraw. Each import still needs to be checked against the
exact exported symbol and calling convention used by this executable.

## Main identified integration gap: FMOD

The executable imports these FMOD symbols:

- `_FSOUND_SetSFXMasterVolume@4`
- `_FSOUND_PlaySound@8`
- `_FSOUND_SetPaused@8`
- `_FSOUND_SetPan@8`
- `_FSOUND_SetVolume@8`
- `_FSOUND_SetFrequency@8`
- `_FSOUND_PlaySoundEx@16`
- `_FSOUND_Sample_Free@4`
- `_FSOUND_Close@0`
- `_FSOUND_GetVersion@0`
- `_FSOUND_SetMemorySystem@20`
- `_FSOUND_Init@12`
- `_FSOUND_Sample_Load@20`
- `_FSOUND_StopSound@4`

The current runtime documents Miles Sound System support, not an FMOD shim.
A small FMOD compatibility module is therefore required. It should load the
provided OGG samples and map sample/channel operations onto the runtime's
SDL2-backed audio facilities. Stub returns alone would silence the game and
may break its startup checks.

## Runtime integration sequence

1. Place the three generated C files and function header under
   `android/app/src/main/cpp/reconstructed/`; compile the generated C and
   dispatch table with `runtime/recomp32/recomp_types.h`.
2. Compile the required `runtime/win32hle` host, PE loader, memory, kernel32,
   user32, gdi32, DirectDraw, DirectInput, DirectSound and WinMM sources into
   the Android native library. Check Android/Bionic compatibility and optional
   SDL_ttf dependencies before enabling each source.
3. Add FMOD import registration and implement the 14 imported FMOD functions.
4. Configure the guest drive mapping to the app-private imported game folder,
   then call `recomp_host_init()`, permissive PE boot, and the lifted entry
   point on the SDL game thread.
5. Connect the already prepared Android tap adapter to the HLE mouse-message
   queue and present the runtime framebuffer through the SDL Android surface.
6. Test startup, menus, gameplay, audio and repeated tap input on a physical
   ARM64 device before enabling the Play button.

## Important status

This is an integration assessment, not a claim that the lifted C is already
compiled into the APK. The supplied archive is currently attached to the
conversation; it has not been uploaded into the Git repository. The original
game is not yet playable on Android.
