include_directories (../)

add_definitions (-DPROJECT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")
file (COPY testsuite/test-audio.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(AudioFile_fuzz AudioFile_fuzz.cpp)
target_link_libraries (AudioFile_fuzz AudioFile)