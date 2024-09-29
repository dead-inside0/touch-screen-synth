#ifndef TOUCHSYNTH_AUDIOENGINE_H
#define TOUCHSYNTH_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include "Synth.h"
#pragma once

using namespace oboe;

class AudioEngine : public AudioStreamCallback{
public:

    std::shared_ptr<AudioStream> stream;
    void init();
    void close();
    void play();
    void pause();
    void changeFreq(float f);
    void changeAmp(float a);
    float frequency = 440.f;
    float amplitude = 0.5f;
    bool playing = false;

    Synth waveTableSynth = Synth();
    DataCallbackResult
    onAudioReady(AudioStream *audioStream, void *audioData, int32_t numFrames) override;
};

#endif //TOUCHSYNTH_AUDIOENGINE_H
