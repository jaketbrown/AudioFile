add_executable(AudioFile_fuzz AudioFile_fuzz.cpp)

target_compile_options(AudioFile_fuzz PUBLIC -fsanitize=fuzzer,address,undefined)
target_link_options(AudioFile_fuzz PUBLIC -fsanitize=fuzzer,address,undefined)

file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testsuite)
file (COPY testsuite/test-audio.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/testsuite)



target_link_libraries(AudioFile_fuzz PUBLIC AudioFile)