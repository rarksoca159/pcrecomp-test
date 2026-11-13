#include "android_input_bridge.h"
#include "win32hle.h"

#include <stdint.h>

static SDL_FingerID g_touch_id;
static int g_touch_active;
static int g_touch_x, g_touch_y;

static int clamp_coord(int value, int limit) {
    if (value < 0) return 0;
    if (value >= limit) return limit - 1;
    return value;
}

/* Optional Android bridge: forward the complete finger gesture through the
 * native touch API. This deliberately does not synthesize USER32 mouse input. */
int spinwin_android_forward_touch(const SDL_Event *event,
                                  int logical_w,
                                  int logical_h) {
    if (!event || logical_w <= 0 || logical_h <= 0) return 0;

    if (event->type == SDL_FINGERDOWN) {
        if (g_touch_active) return 0;
        g_touch_id = event->tfinger.fingerId;
        g_touch_active = 1;
    } else if (!g_touch_active || event->tfinger.fingerId != g_touch_id ||
               (event->type != SDL_FINGERMOTION && event->type != SDL_FINGERUP)) {
        return 0;
    }

    if (event->type == SDL_FINGERDOWN || event->type == SDL_FINGERMOTION ||
        event->type == SDL_FINGERUP) {
        g_touch_x = clamp_coord((int)(event->tfinger.x * logical_w), logical_w);
        g_touch_y = clamp_coord((int)(event->tfinger.y * logical_h), logical_h);
    }

    if (event->type == SDL_FINGERDOWN) {
        hle_input_touch_sync(HLE_WM_TOUCHMOVE, g_touch_x, g_touch_y);
        hle_input_touch_sync(HLE_WM_TOUCHDOWN, g_touch_x, g_touch_y);
    } else if (event->type == SDL_FINGERMOTION) {
        hle_input_touch_sync(HLE_WM_TOUCHMOVE, g_touch_x, g_touch_y);
    } else if (event->type == SDL_FINGERUP) {
        hle_input_touch_sync(HLE_WM_TOUCHMOVE, g_touch_x, g_touch_y);
        hle_input_touch_sync(HLE_WM_TOUCHUP, g_touch_x, g_touch_y);
        g_touch_active = 0;
    }
    return 1;
}
