#include <stdint.h>
#include <stdio.h>
#include <climits>
#include <math.h>
#include <stddef.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "AudioFile.h"


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    // Get the bytes into a vector<uint8_t>
    FuzzedDataProvider provider(data, size);
    int bitDepth = provider.ConsumeIntegralInRange(1, 24);
    int sampleRate = provider.ConsumeIntegralInRange(44100, 48000);
    std::vector<uint8_t> consumedBytes = provider.ConsumeRemainingBytes<uint8_t>();
    // An empty or small byte vector doesn't help us.
    if (consumedBytes.size() < 12) {
        return 0;
    }
    // Prepend a valid header the target is expecting
    std::string header = "RIFF";
    // Convert the string to a vector of uint8_t
    std::vector<uint8_t> strVec(header.begin(), header.end());

    // Prepend the string vector to the original vector
    consumedBytes.insert(consumedBytes.begin(), strVec.begin(), strVec.end());

    // Test the loadFromMemory Function
    AudioFile<uint8_t> audioFile;
    // disable logging
    audioFile.shouldLogErrorsToConsole(false);
    audioFile.loadFromMemory(consumedBytes);
    audioFile.setBitDepth (bitDepth);
    audioFile.setSampleRate (sampleRate);

    return 0;
}