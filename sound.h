//
// Created by xsixel on 10/27/25.
//

#ifndef SORTINGALGORITHMSVISUALIZATION_SOUND_H
#define SORTINGALGORITHMSVISUALIZATION_SOUND_H

typedef struct {
    Mix_Chunk *chunk;
    Uint8     *buffer;
    int        channel;
    int        wait_ms;
} CleanupData;

bool sound_init();

Mix_Chunk* sound_load_effect(const char* filepath);
int sound_play_effect(Mix_Chunk* chunk, int loop); //(loop : 0=play once, -1=loop forever)
void sound_free_effect(Mix_Chunk* chunk);

Mix_Music* sound_load_music(const char* filepath);
int sound_play_music(Mix_Music* music, int loop); //(loop : 0
void sound_free_music(Mix_Music* music);

void sound_clean(void);

int sound_play_tone(float freq_hz, int duration_ms, int volume);
void sound_play_tone_from_value(int value, int max_value, int duration_ms, int volume);


#endif //SORTINGALGORITHMSVISUALIZATION_SOUND_H