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
    std::vector<uint8_t> consumedBytes = provider.ConsumeRemainingBytes<uint8_t>();

    // Prepend a valid header the target is expecting
    std::string header = "RIFF";
    // Convert the string to a vector of uint8_t
    std::vector<uint8_t> strVec(header.begin(), header.end());

    // Prepend the string vector to the original vector
    consumedBytes.insert(consumedBytes.begin(), strVec.begin(), strVec.end());

    AudioFile<double> audioFile;
    // Test the loadFromMemory Function
    audioFile.loadFromMemory(consumedBytes);


    return 0;
}