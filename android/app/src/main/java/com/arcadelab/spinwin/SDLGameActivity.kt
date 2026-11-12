package com.arcadelab.spinwin

import org.libsdl.app.SDLActivity

/**
 * Dedicated SDL2 test surface. The game launcher remains a normal AndroidX activity.
 * SDL2 is linked statically into spinwin_android, so load only that library.
 */
class SDLGameActivity : SDLActivity() {
    override fun getLibraries(): Array<String> = arrayOf("spinwin_android")
}
