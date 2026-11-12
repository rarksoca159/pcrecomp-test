# Spin & Win Android starter

This is an initial Android Studio scaffold, not yet a playable game port.

Implemented:
- landscape launcher screen;
- Android folder picker and private-storage import for the extracted game folder;
- NDK/JNI shell;
- APK build workflow in .github/workflows/android-apk.yml.

The Play button is deliberately disabled until the engine is ported. SpinWin.exe is a
32-bit x86 Windows GUI executable. Its imports include DirectDraw, USER32, GDI32,
WinMM and FMOD. The reconstructed C is machine-code lifting, not original source,
and requires the pcrecomp runtime plus replacements for those Windows APIs.

Open the android/ folder in Android Studio (JDK 17, SDK 35, NDK and CMake installed).
The game files are selected on the device; they are not bundled in this repository.
