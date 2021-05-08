#ifndef TIMEDWAVE_H_INCLUDED
#define TIMEDWAVE_H_INCLUDED

#define OSCILL_SINE 1
#define OSCILL_SQUARE 2
#define OSCILL_TRIANGLE 3
#define OSCILL_PULSE 4

typedef char (*SoundFunction)(void * obj, double TimeStamp);
typedef void (*DisposalFunction)(void * obj);

struct _twave
{
    SoundFunction getAt;
    DisposalFunction dispose;
    void * additiveData;
    float deltaTime;
};

typedef struct _twave ITimedWave;

char getSoundAt(ITimedWave * itw, double TimeStamp);

struct _oscill
{
    double frequency;
    char amplitude;
    unsigned int lambda;
    float period;
    unsigned int type;
};

typedef struct _oscill Oscillation;

char OscillationFunction(void * data, double TimeStamp);
ITimedWave * newOscillation(unsigned int type, char amplitude, double frequency, unsigned int sampleRate);
void OscillationDispose(void * data);

int __makeConvertible(int target);

#endif // TIMEDWAVE_H_INCLUDED
