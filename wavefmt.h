#ifndef WAVEFMT_H_INCLUDED
#define WAVEFMT_H_INCLUDED

#define WCONST_RIFF 0x46464952
#define WCONST_WAVE 0x45564157
#define WCONST_fmt 0x20746d66
#define WCONST_PCM 1
#define WCONST_data 0x61746164

#include <stdio.h>

struct _waveHeader
{
    unsigned int chunkId;
    unsigned int chunkSize;
    unsigned int format;
    unsigned int subchunk1Id;
    unsigned int subchunk1Size;
    unsigned short audioFormat;
    unsigned short numChannels;
    unsigned int sampleRate;
    unsigned int byteRate;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
    unsigned int subchunk2Id;
    unsigned int subchunk2Size;
};

typedef struct _waveHeader WHEADER;

int writeWaveIntoFile(FILE * f, ITimedWave * itw, double PlayTime);

WHEADER * getHeaderFromFile(FILE * f);
WHEADER * buildWaveHeader(ITimedWave * itw, double PlayTime);

#endif // WAVEFMT_H_INCLUDED
