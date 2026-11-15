/*
 * fmod.c - FMOD 3.x FSOUND compatibility for Spin & Win.
 *
 * OGG samples are decoded to signed 16-bit PCM with stb_vorbis. Sample and
 * channel state is mixed by dsound.c's existing SDL2 audio callback.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "win32hle.h"

#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"
#undef STB_VORBIS_HEADER_ONLY

#define FMOD_MAX_SAMPLES 128
#define FSOUND_LOOP_NORMAL 0x00000002u
#define FSOUND_MONO        0x00000020u
#define FSOUND_STEREO      0x00000040u

typedef struct {
    uint32_t token;
    int mixer_id;
    int16_t *pcm;
} fmod_sample;

static fmod_sample g_samples[FMOD_MAX_SAMPLES];

static fmod_sample *sample_by_token(uint32_t token) {
    if (!token) return NULL;
    for (int i = 0; i < FMOD_MAX_SAMPLES; i++)
        if (g_samples[i].token == token) return &g_samples[i];
    return NULL;
}

static void f_SetSFXMasterVolume(void) {
    hle_audio_fmod_set_master((int32_t)A32(0));
    RETV(1);
}
static void f_PlaySound(void) {
    fmod_sample *s = sample_by_token(A32(1));
    int channel = s ? hle_audio_fmod_play(s->mixer_id, (int32_t)A32(0), 0) : -1;
    RET(channel, 2);
}
static void f_SetPaused(void) {
    hle_audio_fmod_set_paused((int32_t)A32(0), (int32_t)A32(1));
    RETV(2);
}
static void f_SetPan(void) {
    hle_audio_fmod_set_pan((int32_t)A32(0), (int32_t)A32(1));
    RETV(2);
}
static void f_SetVolume(void) {
    hle_audio_fmod_set_volume((int32_t)A32(0), (int32_t)A32(1));
    RETV(2);
}
static void f_SetFrequency(void) {
    hle_audio_fmod_set_frequency((int32_t)A32(0), (int32_t)A32(1));
    RETV(2);
}
static void f_PlaySoundEx(void) {
    fmod_sample *s = sample_by_token(A32(1));
    int channel = s ? hle_audio_fmod_play(s->mixer_id, (int32_t)A32(0), (int32_t)A32(3) != 0) : -1;
    RET(channel, 4);
}
static void f_SampleFree(void) {
    uint32_t token = A32(0);
    fmod_sample *s = sample_by_token(token);
    if (s) {
        hle_audio_fmod_sample_free(s->mixer_id);
        free(s->pcm);
        hle_free(hle_ptr(s->token));
        memset(s, 0, sizeof *s);
    }
    RET(s ? 1 : 0, 1);
}
static void f_Close(void) {
    hle_audio_fmod_close();
    RETV(0);
}
static void f_GetVersion(void) {
    /* The executable compares this as a float and requires FMOD >= 3.71. */
    RET(0x406D70A4u, 0);
}
static void f_SetMemorySystem(void) { RET(1, 5); }
static void f_Init(void) {
    int ok = hle_audio_fmod_init((int32_t)A32(0), (int32_t)A32(1));
    fprintf(stderr, "[fmod] FSOUND_Init: %s (%d Hz, %d channels)\n",
            ok ? "OK" : "failed", (int32_t)A32(0), (int32_t)A32(1));
    RET(ok, 3);
}
static void f_SampleLoad(void) {
    const char *filename = ASTR(1);
    uint32_t mode = A32(2);
    int source_channels = 0, sample_rate = 0;
    short *decoded = NULL;
    int frames = filename ? stb_vorbis_decode_filename(filename, &source_channels, &sample_rate, &decoded) : -1;
    if (frames <= 0 || !decoded || source_channels < 1 || sample_rate <= 0) {
        fprintf(stderr, "[fmod] could not load OGG sample: %s\n", filename ? filename : "(null)");
        free(decoded);
        RET(0, 5);
    }

    int output_channels = (mode & FSOUND_MONO) ? 1 :
                          (mode & FSOUND_STEREO) ? 2 :
                          (source_channels == 1 ? 1 : 2);
    if (source_channels > 2 && output_channels == 2) output_channels = 2;
    if ((uint64_t)frames * (uint64_t)output_channels > (uint64_t)INT_MAX / sizeof(int16_t)) {
        free(decoded);
        RET(0, 5);
    }

    int16_t *pcm = decoded;
    if (output_channels != source_channels) {
        pcm = (int16_t *)malloc((size_t)frames * (size_t)output_channels * sizeof(int16_t));
        if (!pcm) {
            free(decoded);
            RET(0, 5);
        }
        for (int f = 0; f < frames; f++) {
            if (output_channels == 1) {
                int sum = 0;
                for (int c = 0; c < source_channels; c++)
                    sum += decoded[(size_t)f * (size_t)source_channels + (size_t)c];
                pcm[f] = (int16_t)(sum / source_channels);
            } else {
                int left = 0, right = 0, nl = 0, nr = 0;
                for (int c = 0; c < source_channels; c++) {
                    if ((c & 1) == 0) left += decoded[(size_t)f * (size_t)source_channels + (size_t)c], nl++;
                    else right += decoded[(size_t)f * (size_t)source_channels + (size_t)c], nr++;
                }
                if (!nr) right = left, nr = nl;
                pcm[2 * f] = (int16_t)(left / (nl ? nl : 1));
                pcm[2 * f + 1] = (int16_t)(right / (nr ? nr : 1));
            }
        }
        free(decoded);
    }

    int mixer_id = hle_audio_fmod_sample_create(pcm, (uint32_t)frames,
                                                  output_channels, sample_rate,
                                                  (mode & FSOUND_LOOP_NORMAL) != 0);
    if (mixer_id < 0) {
        free(pcm);
        RET(0, 5);
    }

    int slot = -1;
    for (int i = 0; i < FMOD_MAX_SAMPLES; i++)
        if (!g_samples[i].token) { slot = i; break; }
    if (slot < 0) {
        hle_audio_fmod_sample_free(mixer_id);
        free(pcm);
        RET(0, 5);
    }

    void *token_mem = hle_alloc(32);
    if (!token_mem) {
        hle_audio_fmod_sample_free(mixer_id);
        free(pcm);
        RET(0, 5);
    }
    uint32_t token = hle_va(token_mem);
    g_samples[slot].token = token;
    g_samples[slot].mixer_id = mixer_id;
    g_samples[slot].pcm = pcm;
    fprintf(stderr, "[fmod] loaded %s (%d frames, %d ch, %d Hz%s)\n",
            filename, frames, output_channels, sample_rate,
            (mode & FSOUND_LOOP_NORMAL) ? ", loop" : "");
    RET(token, 5);
}
static void f_StopSound(void) {
    int ok = hle_audio_fmod_stop((int32_t)A32(0));
    RET(ok, 1);
}

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
