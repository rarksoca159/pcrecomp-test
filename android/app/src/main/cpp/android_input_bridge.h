#ifndef SPINWIN_ANDROID_INPUT_BRIDGE_H
#define SPINWIN_ANDROID_INPUT_BRIDGE_H

#include <SDL.h>

/*
 * Forward one SDL2 touch event to the pcrecomp Win32 HLE input system.
 * Call this from the SDL event loop once win32hle is linked into the app.
 * logical_w/logical_h must match the virtual game display dimensions.
 *
 * Returns 1 when the event was consumed as a primary touch, otherwise 0.
 */
int spinwin_android_forward_touch(const SDL_Event *event,
                                  int logical_w,
                                  int logical_h);

#endif
