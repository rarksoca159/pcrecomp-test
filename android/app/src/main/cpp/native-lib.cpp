#include <jni.h>
#include <SDL.h>
#include <cmath>

extern "C" JNIEXPORT jstring JNICALL
Java_com_arcadelab_spinwin_MainActivity_nativeEngineStatus(JNIEnv* env, jobject) {
    SDL_version version{};
    SDL_GetVersion(&version);
    char message[128];
    SDL_snprintf(message, sizeof(message),
                 "SDL2 Android runtime: %u.%u.%u",
                 version.major, version.minor, version.patch);
    return env->NewStringUTF(message);
}

static void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; ++y) {
        const int halfWidth = static_cast<int>(std::sqrt(
            static_cast<double>(radius * radius - y * y)));
        SDL_RenderDrawLine(renderer, cx - halfWidth, cy + y,
                           cx + halfWidth, cy + y);
    }
}

extern "C" int SDL_main(int, char**) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    SDL_Window* window = SDL_CreateWindow(
        "Spin & Win - SDL2 Android Test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        960, 540, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 3;
    }

    SDL_RenderSetLogicalSize(renderer, 960, 540);
    bool running = true;
    bool hasTouch = false;
    int touchX = 480;
    int touchY = 270;
    Uint32 tick = 0;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION) {
                hasTouch = true;
                touchX = static_cast<int>(event.tfinger.x * 960.0f);
                touchY = static_cast<int>(event.tfinger.y * 540.0f);
            }
            if (event.type == SDL_FINGERUP) hasTouch = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        ++tick;
        SDL_SetRenderDrawColor(renderer, 91, 12, 17, 255);
        SDL_RenderClear(renderer);

        // A simple wheel-shaped test graphic proves the SDL renderer is active.
        SDL_SetRenderDrawColor(renderer, 248, 218, 180, 255);
        SDL_Rect panel{150, 42, 660, 456};
        SDL_RenderDrawRect(renderer, &panel);

        const int pulse = 4 + static_cast<int>((std::sin(tick * 0.035) + 1.0) * 5.0);
        SDL_SetRenderDrawColor(renderer, 244, 190, 65, 255);
        for (int radius = 154; radius >= 136; radius -= 9)
            SDL_RenderDrawCircle; // placeholder removed below

        // Draw concentric rings using horizontal scan lines.
        for (int radius = 150; radius >= 136; radius -= 7) {
            SDL_SetRenderDrawColor(renderer, 244, 190, 65, 255);
            for (int y = -radius; y <= radius; ++y) {
                const int x = static_cast<int>(std::sqrt(
                    static_cast<double>(radius * radius - y * y)));
                SDL_RenderDrawLine(renderer, 480 - x, 260 + y, 480 + x, 260 + y);
            }
        }
        SDL_SetRenderDrawColor(renderer, 91, 12, 17, 255);
        drawFilledCircle(renderer, 480, 260, 112);
        SDL_SetRenderDrawColor(renderer, 248, 218, 180, 255);
        drawFilledCircle(renderer, 480, 260, 9);

        // Rotating pointer/marker animation.
        const double angle = tick * 0.025;
        const int px = 480 + static_cast<int>(std::cos(angle) * 126.0);
        const int py = 260 + static_cast<int>(std::sin(angle) * 126.0);
        SDL_SetRenderDrawColor(renderer, 255, 226, 125, 255);
        drawFilledCircle(renderer, px, py, 10 + pulse / 3);

        if (hasTouch) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect crossH{touchX - 22, touchY - 2, 44, 4};
            SDL_Rect crossV{touchX - 2, touchY - 22, 4, 44};
            SDL_RenderFillRect(renderer, &crossH);
            SDL_RenderFillRect(renderer, &crossV);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
