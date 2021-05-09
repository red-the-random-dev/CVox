#include <stdio.h>
#include <stdlib.h>

#include "cvox/timedwave.h"
#include "cvox/wavefmt.h"
#include "cvox/conjwave.h"

int main()
{

    ITimedWave * x = newOscillation(1, 128, 1000.0, 48000);
    ITimedWave * y = newOscillation(1, 128, 2000.0, 48000);
    double * times = (double*) malloc(sizeof(double)*2);
    ITimedWave ** a = (ITimedWave**) malloc(sizeof(ITimedWave*)*1);
    times[0] = ((Oscillation*)x->additiveData)->period;
    times[1] = ((Oscillation*)y->additiveData)->period;
    a[0] = x;
    a[1] = y;
    ITimedWave * mix = newConjoinedWave(48000, 2, a, times, 0);
    printf("Creating test tone file...\n");
    FILE * f = fopen("1000hz_test_tone.wav", "w");
    writeWaveIntoFile(f, x, 5);
    fclose(f);
    printf("Creating conjoined wave file...\n");
    f = fopen("1000hz..2000hz_test_tone.wav", "w");
    writeWaveIntoFile(f, mix, 5);
    printf("Test tone files created.\n");
    fclose(f);
    printf("Finalizing wave object...\n");
    mix->dispose(mix);
    x->dispose(x);
    y->dispose(y);
    return 0;
}
