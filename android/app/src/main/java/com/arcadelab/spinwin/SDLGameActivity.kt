package com.arcadelab.spinwin

import org.libsdl.app.SDLActivity
import java.io.File

/** Runs SpinWin.exe through the reconstructed Win32 HLE runtime. */
class SDLGameActivity : SDLActivity() {
    protected override fun getLibraries(): Array<String> = arrayOf("spinwin_android")

    protected override fun getArguments(): Array<String> =
        arrayOf(File(filesDir, "spinwin").absolutePath)
}
