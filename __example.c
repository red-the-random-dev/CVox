#include <stdio.h>
#include <stdlib.h>

#include "timedwave.h"
#include "wavefmt.h"

int main()
{
    ITimedWave * x = newOscillation(1, 128, 1000.0, 48000);
    printf("%f\n", x->deltaTime);
    for (double i = 0.0; i < 0.25; i += x->deltaTime)
    {
        printf("%d ", getSoundAt(x, i));
    }
    printf("\b\n");
    FILE * f = fopen("1000hz_test_tone.wav", "w");
    writeWaveIntoFile(f, x, 1);
    x->dispose(x);
    return 0;
}
