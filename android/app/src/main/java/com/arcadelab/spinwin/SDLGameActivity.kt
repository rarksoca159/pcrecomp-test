package com.arcadelab.spinwin

import org.libsdl.app.SDLActivity
import android.content.pm.ActivityInfo
import java.io.File

/** Runs SpinWin.exe through the reconstructed Win32 HLE runtime. */
class SDLGameActivity : SDLActivity() {
    /** Keep SDL's game surface in left-to-right landscape, even if SDL requests portrait. */
    override fun setOrientationBis(w: Int, h: Int, resizable: Boolean, hint: String) {
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
    }

    protected override fun getLibraries(): Array<String> = arrayOf("spinwin_android")

    protected override fun getArguments(): Array<String> =
        arrayOf(File(filesDir, "spinwin").absolutePath)
}
