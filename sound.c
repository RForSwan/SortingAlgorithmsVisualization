//
// Created by xsixel on 10/27/25.
//

#include "settings.h"


bool sound_init(void) {
    int flags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(flags) & flags) != flags) {
        // not fatal, but log
        fprintf(stderr, "Mix_Init warning: %s\n", Mix_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio error: %s\n", Mix_GetError());
        return false;
    }
    Mix_AllocateChannels(16);
    return true;
}

Mix_Chunk* sound_load_effect(const char* path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path);
    if (!chunk) {
        return NULL;
    }
    return chunk;
}

int sound_play_effect(Mix_Chunk* chunk, int loops) {
    if (!chunk) return -1;
    int ch = Mix_PlayChannel(-1, chunk, loops);
    if (ch == -1) fprintf(stderr, "Mix_PlayChannel error: %s\n", Mix_GetError());
    return ch;
}

void sound_free_effect(Mix_Chunk* chunk) {
    if (chunk) Mix_FreeChunk(chunk);
}

Mix_Music* sound_load_music(const char* path) {
    Mix_Music* m = Mix_LoadMUS(path);
    if (!m) fprintf(stderr, "Mix_LoadMUS('%s') error: %s\n", path, Mix_GetError());
    return m;
}

int sound_play_music(Mix_Music* music, int loops) {
    if (!music) return -1;
    if (Mix_PlayMusic(music, loops) == -1) {
        fprintf(stderr, "Mix_PlayMusic error: %s\n", Mix_GetError());
        return -1;
    }
    return 0;
}

void sound_stop_music(void) {
    Mix_HaltMusic();
}

void sound_free_music(Mix_Music* music) {
    if (music) Mix_FreeMusic(music);
}

void sound_clean(void) {
    Mix_HaltChannel(-1); // stop all channels
    Mix_HaltMusic();
    Mix_CloseAudio();
    Mix_Quit();
}

static int cleanup_thread(void *pdata)
{
    CleanupData *cd = (CleanupData*)pdata;
    if (!cd) return -1;
    SDL_Delay(cd->wait_ms + 50);
    if (cd->channel >= 0) Mix_HaltChannel(cd->channel);
    if (cd->chunk) Mix_FreeChunk(cd->chunk);
    if (cd->buffer) free(cd->buffer);
    free(cd);
    return 0;
}


/* Synthesizes a sine wave (AUDIO_S16LSB)
   play the wave with the SDL MIXER
   freq_hz: frequency in Hz
   duration_ms: duration in milliseconds
   volume: 0..128 (SDL_mixer scale)*/

int sound_play_tone(float freq_hz, int duration_ms, int volume)
{
    if (freq_hz <= 0.0f || duration_ms <= 0) return -1;
    const int sample_rate = 44100;
    const int channels = 1; // mono
    const int bytes_per_sample = 2; // S16
    int samples = (sample_rate * duration_ms) / 1000;
    if (samples < 1) samples = 1;

    // Allocate buffer for signed 16-bit samples
    int16_t *samples_buf = malloc(samples * sizeof(int16_t));
    if (!samples_buf) return -1;

    const double two_pi = 2.0 * M_PI;
    double amplitude = 28000.0 * (fminf(128, fmaxf(0, volume)) / 128.0f);

    for (int i = 0; i < samples; ++i) {
        double t = (double)i / (double)sample_rate;
        double s = sin(two_pi * freq_hz * t);
        samples_buf[i] = (int16_t)(s * amplitude);
    }

    // Create Mix_Chunk from raw buffer; SDL_mixer must have been opened with AUDIO_S16LSB, 44100
    Uint8 *raw = (Uint8*)samples_buf;
    Uint32 len = samples * bytes_per_sample * channels;

    Mix_Chunk *chunk = Mix_QuickLoad_RAW(raw, len);
    if (!chunk) {
        free(samples_buf);
        return -1;
    }

    // Set volume on chunk (0..MIX_MAX_VOLUME)
    Mix_VolumeChunk(chunk, volume);

    int channel = Mix_PlayChannel(-1, chunk, 0);
    if (channel == -1) {
        // Failed to play; free resources
        Mix_FreeChunk(chunk);
        free(samples_buf);
        return -1;
    }

    // Spawn cleanup thread to free chunk and buffer after playback
    CleanupData *cd = malloc(sizeof(CleanupData));
    if (!cd) {
        // best effort cleanup: stop channel and free now
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
        free(samples_buf);
        return channel;
    }
    cd->chunk = chunk;
    cd->buffer = raw; // will be freed by cleanup thread
    cd->channel = channel;
    cd->wait_ms = duration_ms;

    SDL_Thread *thr = SDL_CreateThread(cleanup_thread, "tone_cleanup", cd);
    if (!thr) {
        // If thread creation failed, free immediately (may cut sound)
        Mix_HaltChannel(channel);
        Mix_FreeChunk(chunk);
        free(samples_buf);
        free(cd);
        return channel;
    }
    SDL_DetachThread(thr);

    return channel;
}

/* Map a bar value/index to a frequency and play it.
   value: bar value (or index)
   max_value: maximum bar value (or number of bars)
   duration_ms: duration in ms
   volume: 0..128 */
void sound_play_tone_from_value(int value, int max_value, int duration_ms, int volume)
{
    if (max_value <= 0) return;
    // Map value in [0..max_value] (or 1..max_value) to freq between 220Hz and 1760Hz
    float min_f = 220.0f;   // A3 ~220Hz
    float max_f = 1760.0f;  // A6 ~1760Hz
    float norm = (float)value / (float)max_value;
    if (norm < 0.0f) norm = 0.0f;
    if (norm > 1.0f) norm = 1.0f;
    float freq = min_f + (max_f - min_f) * norm;
    sound_play_tone(freq, duration_ms, volume);
}
