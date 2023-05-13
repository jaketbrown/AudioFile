#include <stdint.h>
#include <stdio.h>
#include <climits>
#include <math.h>
#include <stddef.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "AudioFile.h"


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    float x = provider.ConsumeFloatingPoint<float>();

    AudioFile<double>::AudioBuffer buffer;
    AudioFile<double> audioFile;
    audioFile.load ("testsuite/test-audio.wav");

    buffer.resize (2);

    buffer[0].resize (100000);
    buffer[1].resize (100000);

    int numChannels = 2;
    int numSamplesPerChannel = 100000;
    float sampleRate = 44100.f;
    float frequency = 440.f;

    for (int i = 0; i < numSamplesPerChannel; i++)
    {
        //float sample = sinf (2. * M_PI * ((float) i / sampleRate) * frequency) ;
        float sample = sinf (2. * M_PI * ((float) i / sampleRate) * (frequency + x));
        for (int channel = 0; channel < numChannels; channel++)
            buffer[channel][i] = sample * 0.5;
    }

    audioFile.setAudioBuffer(buffer);


    return 0;
}