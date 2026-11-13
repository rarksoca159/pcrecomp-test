# Native engine status

The Android native engine is integrated with SDL2 and the reconstructed
Spin & Win guest code. The JNI/SDL entry point receives the imported game
folder, maps it as the guest C: drive, initializes the Win32 HLE host, opens the
game display, loads `SpinWin.exe`, and runs the lifted game code.

The Android port is playable. Remaining known problems are Android keyboard
and high-score name entry, unreliable single-click dialog interaction, and
game audio. See [../../README.md](../../README.md) for the current status and
testing priorities.
