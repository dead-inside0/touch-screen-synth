#ifndef TOUCHSYNTH_SYNTH_H
#define TOUCHSYNTH_SYNTH_H

#include <vector>
#pragma once

class Synth {
public:
    enum WaveType {
        SINE,
        SQUARE
    };
    static std::vector<float> wavetable;
    int wavetableLength = 4096;
    int sampleRate = 48000;

    float phase = 0.0f;
    float phaseIncrement = 0.0f;
    float frequency = 440.0f;

    Synth() {
        wavetable.resize(wavetableLength);
        for(int i = 0; i < wavetableLength; i++) {
            wavetable[i] = sinf((2 * M_PI * i) / wavetableLength);
        }
        this->calculatePhaseIncrement();
    }

    void calculatePhaseIncrement();
    float getNextSample(WaveType type);
    void changeFreq(float f);
};

#endif //TOUCHSYNTH_SYNTH_H
