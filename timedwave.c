#ifndef TIMEDWAVE_C_INCLUDED
#define TIMEDWAVE_C_INCLUDED

#define PI 3.1415926535f
#include <math.h>
#include <stdlib.h>

typedef char (*SoundFunction)(void * obj, double TimeStamp);
typedef void (*DisposalFunction)(void * obj);

int __makeConvertible(int target)
{
    int pre_def = (target >= 0 ? target : 0 - target);
    return (pre_def < 256 ? pre_def : 255);
}

struct _twave
{
    SoundFunction getAt;
    DisposalFunction dispose;
    void * additiveData;
    float deltaTime;
};

typedef struct _twave ITimedWave;

struct _oscill
{
    double frequency;
    char amplitude;
    unsigned int lambda;
    float period;
    unsigned int type;
};

typedef struct _oscill Oscillation;

char getSoundAt(ITimedWave * itw, double TimeStamp)
{
    return itw->getAt(itw->additiveData, TimeStamp);
}

char OscillationFunction(void * data, double TimeStamp)
{
    Oscillation * osc = (Oscillation*) data;
    switch (osc->type)
    {
        case 1:
        {
            double arg = sin(TimeStamp*PI*osc->frequency)*sin(TimeStamp*PI*osc->frequency)*osc->amplitude;
            // printf("\nSine function triggered: %d %f %f ", osc->amplitude, TimeStamp, arg);
            return ((char)__makeConvertible((int)arg));
        }
        default:
        {
            return 0;
        }
    }
}

void OscillationDispose(void * data)
{
    ITimedWave * x = (ITimedWave*) data;
    Oscillation * y = (Oscillation*) x->additiveData;

    free(y);
    free(data);
}

ITimedWave * newOscillation(unsigned int type, char amplitude, double frequency, unsigned int sampleRate)
{
    ITimedWave * x = (ITimedWave*) malloc(sizeof(ITimedWave));
    Oscillation * y = (Oscillation*) malloc(sizeof(Oscillation));
    y->amplitude = amplitude;
    x->deltaTime = (1.0 / sampleRate);
    y->type = type;
    y->frequency = frequency;
    y->lambda = (unsigned int) (sampleRate / frequency);
    y->period = (float) (1.0 * y->lambda / sampleRate);

    x->additiveData = (void*) y;
    x->getAt = &OscillationFunction;
    x->dispose = &OscillationDispose;

    return x;
}

#endif // TIMEDWAVE_C_INCLUDED
