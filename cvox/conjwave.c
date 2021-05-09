#ifndef CONJWAVE_C_INCLUDED
#define CONJWAVE_C_INCLUDED
#include "timedwave.h"
#include "conjwave.h"
#include <stdlib.h>
#include <stdio.h>

ITimedWave * newConjoinedWave(unsigned int sampleRate, size_t waveCount, ITimedWave ** waves, double * waveLengths, char finalizeAtEnd)
{
    double * waveStamps = (double*) malloc(sizeof(double) * waveCount);
    double cur = 0;
    // printf("Creating timestamp array...\n");
    for (int i = 0; i < waveCount; i++)
    {
        waveStamps[i] = cur;
        cur += waveLengths[i];
    }
    // printf("DOne making timetamp array.\n");
    ConjoinedWave * cw = malloc(sizeof(ConjoinedWave));
    cw->length = cur;
    cw->waves = waves;
    cw->waveStamps = waveStamps;
    cw->finalizeWavesAtEnd = finalizeAtEnd;
    cw->wcount = waveCount;
    ITimedWave * itw = malloc(sizeof(ITimedWave));
    itw->additiveData = (void*) cw;
    itw->deltaTime = 1.0 / sampleRate;
    itw->dispose = &conjoinedWaveDisposal;
    itw->getAt = &conjoinedWaveSoundMethod;

    return itw;
}

void conjoinedWaveDisposal(void * obj)
{
    ITimedWave * itw = (ITimedWave*) obj;
    ConjoinedWave * cw = (ConjoinedWave*) itw->additiveData;

    if (cw->finalizeWavesAtEnd != 0)
    {
        for (int i = 0; i < cw->wcount; i++)
        {
            cw->waves[i]->dispose(cw->waves[i]);
            free(cw->waves[i]);
        }
        free(cw->waves);
    }
    free(cw->waveStamps);
    free(cw);
    free(itw);
}

unsigned char conjoinedWaveSoundMethod(void * data, double TimeStamp)
{
    ConjoinedWave * cw = (ConjoinedWave*) data;

    while (TimeStamp > cw->length)
    {
        TimeStamp -= cw->length;
    }

    while (TimeStamp < 0)
    {
        TimeStamp += cw->length;
    }

    int pick = 0;
    for (;pick < cw->wcount-1; pick++)
    {
        if (TimeStamp < cw->waveStamps[pick+1] && TimeStamp >= cw->waveStamps[pick])
        {
            break;
        }
    }

    double newStamp = TimeStamp - cw->waveStamps[pick];
    return getSoundAt(cw->waves[pick], newStamp);
}

#endif // CONJWAVE_C_INCLUDED
