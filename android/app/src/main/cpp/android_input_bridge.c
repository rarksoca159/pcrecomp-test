#include "android_input_bridge.h"
#include "win32hle.h"

#include <stdint.h>

/* Win32 messages used by win32hle's hle_input_mouse API. */
#define SW_WM_MOUSEMOVE   0x0200u
#define SW_WM_LBUTTONDOWN 0x0201u
#define SW_WM_LBUTTONUP   0x0202u

static int clamp_coord(int value, int limit) {
    if (value < 0) return 0;
    if (value >= limit) return limit - 1;
    return value;
}

/*
 * Spin & Win uses a simple left-click control scheme. Treat each Android tap
 * as one complete click at the tapped location. Do not emulate a held button,
 * dragging, right-click, or multi-touch.
 */
int spinwin_android_forward_touch(const SDL_Event *event,
                                  int logical_w,
                                  int logical_h) {
    if (!event || logical_w <= 0 || logical_h <= 0) return 0;

    if (event->type != SDL_FINGERDOWN) return 0;

    const int x = clamp_coord((int)(event->tfinger.x * logical_w), logical_w);
    const int y = clamp_coord((int)(event->tfinger.y * logical_h), logical_h);

    hle_input_cursor(x, y);
    hle_input_mouse(SW_WM_MOUSEMOVE, x, y);

    /* Synthesize a complete left click from one screen tap. */
    hle_input_mouse(SW_WM_LBUTTONDOWN, x, y);
    hle_input_mouse(SW_WM_LBUTTONUP, x, y);

    return 1;
}
