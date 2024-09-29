#include "Synth.h"

void Synth::calculatePhaseIncrement() {
    this->phaseIncrement = (frequency * wavetableLength) / sampleRate;
}

float Synth::getNextSample(Synth::WaveType type) {
    float sample = wavetable[static_cast<int>(phase)];
    phase += phaseIncrement;
    while(phase > wavetableLength) {
        phase -= wavetableLength;
    }
    switch(type) {
        case SINE :
            return sample;
        case SQUARE :
            return sample>=0 ? 1 : -1;
    }
}

void Synth::changeFreq(float f) {
    this->frequency = f;
    calculatePhaseIncrement();
}
