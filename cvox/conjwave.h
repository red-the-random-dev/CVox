#ifndef CONJWAVE_H_INCLUDED
#define CONJWAVE_H_INCLUDED
#include "timedwave.h"
#include <stdlib.h>

struct _conwave
{
    size_t wcount;
    ITimedWave ** waves;
    double length;
    double * waveStamps;
    char finalizeWavesAtEnd;
};

typedef struct _conwave ConjoinedWave;

ITimedWave * newConjoinedWave(unsigned int sampleRate, size_t waveCount, ITimedWave ** waves, double * waveLength, char finalizeAtEnd);
unsigned char conjoinedWaveSoundMethod(void * data, double TimeStamp);
void conjoinedWaveDisposal(void * obj);

#endif // CONJWAVE_H_INCLUDED
