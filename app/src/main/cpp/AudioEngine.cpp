#include <android/log.h>
#include "AudioEngine.h"
#include "Synth.h"

void AudioEngine::init() {
    __android_log_print(ANDROID_LOG_INFO,"AudioEngine","Starting audio engine...");
    AudioStreamBuilder builder;
    builder.setSharingMode(SharingMode::Exclusive)
        ->setFormat(AudioFormat::Float)
        ->setPerformanceMode(PerformanceMode::LowLatency)
        ->setSampleRate(48000)
        ->setCallback(this)
        ->setChannelCount(1);
    Result result = builder.openStream(stream);
    if(result == Result::OK) {
        __android_log_print(ANDROID_LOG_INFO,"AudioEngine","Successfully opened audio stream");
        stream->requestStart();
    } else {
        __android_log_print(ANDROID_LOG_ERROR,"AudioEngine","Failed to open audio stream");
    }
}

void AudioEngine::close() {
    __android_log_print(ANDROID_LOG_WARN,"AudioEngine","Closing audio stream");
    stream->requestStop();
    stream->close();
}

float db2Amp(float db) {
    return pow(10,(db/20));
}

DataCallbackResult
AudioEngine::onAudioReady(AudioStream *audioStream, void *audioData,
                                         int32_t numFrames) {
    auto *audioBuffer = static_cast<float *>(audioData);

    int numSamples = numFrames * 1;

    for(int i = 0; i < numSamples; i++) {
        if(!playing) {
            *audioBuffer++ = 0;
            continue;
        }
        waveTableSynth.changeFreq(frequency);
        float sample = waveTableSynth.getNextSample(Synth::WaveType::SQUARE) * amplitude;
        *audioBuffer++ = sample;
    }

    return DataCallbackResult::Continue;
}

void AudioEngine::changeFreq(float f) {
    this->frequency = f;
}

void AudioEngine::changeAmp(float a) {
    this->amplitude = a;
}

void AudioEngine::play() {
    this->playing = true;
}

void AudioEngine::pause() {
    this->playing = false;
}
