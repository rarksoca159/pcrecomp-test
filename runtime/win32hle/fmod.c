/*
 * fmod.c - silent FMOD 3.x compatibility for Spin & Win.
 *
 * The original executable imports FMOD's FSOUND API. This first Android
 * compatibility layer supplies valid sample tokens and successful init/
 * control calls so game startup is not stopped by missing FMOD imports.
 * Playback is intentionally silent; SDL audio decoding/mixing is a separate
 * implementation step and is not claimed here.
 */
#include "win32hle.h"

static void f_SetSFXMasterVolume(void) { RETV(1); }
static void f_PlaySound(void)          { RET(0, 2); }
static void f_SetPaused(void)          { RETV(2); }
static void f_SetPan(void)             { RETV(2); }
static void f_SetVolume(void)          { RETV(2); }
static void f_SetFrequency(void)       { RETV(2); }
static void f_PlaySoundEx(void)        { RET(0, 4); }
static void f_SampleFree(void) {
    uint32_t sample = A32(0);
    if (sample) hle_free(hle_ptr(sample));
    RET(1, 1);
}
static void f_Close(void)              { RETV(0); }
static void f_GetVersion(void)         { RET(0x00030075u, 0); }
static void f_SetMemorySystem(void)    { RET(1, 5); }
static void f_Init(void)               { RET(1, 3); }
static void f_SampleLoad(void) {
    void *sample = hle_alloc(32);
    RET(hle_va(sample), 5);
}
static void f_StopSound(void)          { RET(1, 1); }

const win32hle_shim win32hle_fmod[] = {
    { "_FSOUND_SetSFXMasterVolume@4", f_SetSFXMasterVolume },
    { "_FSOUND_PlaySound@8",          f_PlaySound },
    { "_FSOUND_SetPaused@8",          f_SetPaused },
    { "_FSOUND_SetPan@8",             f_SetPan },
    { "_FSOUND_SetVolume@8",          f_SetVolume },
    { "_FSOUND_SetFrequency@8",       f_SetFrequency },
    { "_FSOUND_PlaySoundEx@16",       f_PlaySoundEx },
    { "_FSOUND_Sample_Free@4",        f_SampleFree },
    { "_FSOUND_Close@0",              f_Close },
    { "_FSOUND_GetVersion@0",         f_GetVersion },
    { "_FSOUND_SetMemorySystem@20",   f_SetMemorySystem },
    { "_FSOUND_Init@12",              f_Init },
    { "_FSOUND_Sample_Load@20",       f_SampleLoad },
    { "_FSOUND_StopSound@4",          f_StopSound },
    { 0, 0 }
};
