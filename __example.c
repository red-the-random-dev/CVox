#include <stdio.h>
#include <stdlib.h>

#include "cvox/timedwave.h"
#include "cvox/wavefmt.h"

int main()
{
    ITimedWave * x = newOscillation(1, 128, 1000.0, 48000);
    printf("Creating test tone file...\n");
    FILE * f = fopen("1000hz_test_tone.wav", "w");
    writeWaveIntoFile(f, x, 1);
    printf("Test tone file created.\n");
    x->dispose(x);
    return 0;
}
