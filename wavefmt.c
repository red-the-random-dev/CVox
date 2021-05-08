#ifndef WAVEFMT_C_INCLUDED
#define WAVEFMT_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "timedwave.h"
#include "wavefmt.h"

int writeWaveIntoFile(FILE * f, ITimedWave * itw, double PlayTime)
{
    char * wh = (char*) buildWaveHeader(itw, PlayTime);
    if (wh == NULL)
    {
        return -1;
    }
    for (int i = 0; i < sizeof(WHEADER); i++)
    {
        fputc(wh[i], f);
    }
    free(wh);
    for (double i = 0; i < PlayTime; i += itw->deltaTime)
    {
        fputc(getSoundAt(itw, i), f);
    }
    return 0;
}

WHEADER * buildWaveHeader(ITimedWave * itw, double PlayTime)
{
    WHEADER * wh = malloc(sizeof(WHEADER));
    wh->chunkId = WCONST_RIFF;
    wh->format = WCONST_WAVE;
    wh->subchunk1Id = WCONST_fmt;
    wh->subchunk2Id = WCONST_data;
    wh->subchunk1Size = 16;
    wh->bitsPerSample = 8;
    wh->blockAlign = 1;
    wh->numChannels = 1;
    wh->sampleRate = (unsigned int)(1.0 / itw->deltaTime);
    wh->byteRate = wh->sampleRate;
    wh->audioFormat = 1;
    wh->subchunk2Size = (unsigned int)(wh->sampleRate * PlayTime);
    wh->chunkSize = wh->subchunk2Size+36;

    return wh;
}

#endif // WAVEFMT_C_INCLUDED
