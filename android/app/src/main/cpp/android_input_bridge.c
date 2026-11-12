#include "android_input_bridge.h"
#include "win32hle.h"

#include <stdint.h>

/* Win32 messages used by win32hle's hle_input_mouse API. */
#define SW_WM_MOUSEMOVE   0x0200u
#define SW_WM_LBUTTONDOWN 0x0201u
#define SW_WM_LBUTTONUP   0x0202u

static SDL_FingerID primary_finger;
static int primary_finger_active;

static int clamp_coord(int value, int limit) {
    if (value < 0) return 0;
    if (value >= limit) return limit - 1;
    return value;
}

int spinwin_android_forward_touch(const SDL_Event *event,
                                  int logical_w,
                                  int logical_h) {
    if (!event || logical_w <= 0 || logical_h <= 0) return 0;

    switch (event->type) {
    case SDL_FINGERDOWN:
        if (primary_finger_active) return 0;
        primary_finger = event->tfinger.fingerId;
        primary_finger_active = 1;
        /* fall through: a press also moves the virtual cursor */
        hle_input_cursor(
            clamp_coord((int)(event->tfinger.x * logical_w), logical_w),
            clamp_coord((int)(event->tfinger.y * logical_h), logical_h));
        hle_input_mouse(SW_WM_MOUSEMOVE,
            clamp_coord((int)(event->tfinger.x * logical_w), logical_w),
            clamp_coord((int)(event->tfinger.y * logical_h), logical_h));
        hle_input_mouse(SW_WM_LBUTTONDOWN,
            clamp_coord((int)(event->tfinger.x * logical_w), logical_w),
            clamp_coord((int)(event->tfinger.y * logical_h), logical_h));
        return 1;

    case SDL_FINGERMOTION:
        if (!primary_finger_active ||
            event->tfinger.fingerId != primary_finger) return 0;
        hle_input_cursor(
            clamp_coord((int)(event->tfinger.x * logical_w), logical_w),
            clamp_coord((int)(event->tfinger.y * logical_h), logical_h));
        hle_input_mouse(SW_WM_MOUSEMOVE,
            clamp_coord((int)(event->tfinger.x * logical_w), logical_w),
            clamp_coord((int)(event->tfinger.y * logical_h), logical_h));
        return 1;

    case SDL_FINGERUP:
        if (!primary_finger_active ||
            event->tfinger.fingerId != primary_finger) return 0;
        hle_input_cursor(
            clamp_coord((int)(event->tfinger.x * logical_w), logical_w),
            clamp_coord((int)(event->tfinger.y * logical_h), logical_h));
        hle_input_mouse(SW_WM_LBUTTONUP,
            clamp_coord((int)(event->tfinger.x * logical_w), logical_w),
            clamp_coord((int)(event->tfinger.y * logical_h), logical_h));
        primary_finger_active = 0;
        return 1;
    default:
        return 0;
    }
}
