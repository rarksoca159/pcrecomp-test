# Native engine status

This is only the Android NDK/JNI shell. The recovered C output is not compiled here yet.
SpinWin.exe imports DirectDraw, USER32, GDI32, WinMM and FMOD. The lifted C also needs
the matching pcrecomp runtime. A working port needs runtime integration, Win32 API
compatibility, a graphics renderer, audio replacement and ARM64 validation.
