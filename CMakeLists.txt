#===============================================================================
cmake_minimum_required (VERSION 3.12)

project ("AudioFile" VERSION 1.1.1
                     DESCRIPTION "A simple C++ library for reading and writing audio files."
                     HOMEPAGE_URL "https://github.com/adamstark/AudioFile")

#===============================================================================
include (GNUInstallDirs)

#===============================================================================
option (BUILD_TESTS "Build tests" ON)
option (BUILD_EXAMPLES "Build examples" ON)

#===============================================================================
add_library (${PROJECT_NAME} INTERFACE)

#===============================================================================
if(MSVC)
  # needed for M_PI macro
  add_definitions(-D_USE_MATH_DEFINES)
endif()

#===============================================================================
target_include_directories (
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#===============================================================================
target_compile_features (${PROJECT_NAME} INTERFACE cxx_std_17)

#===============================================================================
if (BUILD_EXAMPLES)
  add_subdirectory (examples)
endif ()

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory (tests)
endif ()

if(AUDIO_FILE_BUILD_FUZZER)
  if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "Fuzzer is only supported on Clang")
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=fuzzer-no-link,address,undefined")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sanitize-recover=undefined")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1")
  add_link_options(-fsanitize=fuzzer-no-link,address,undefined)
  add_subdirectory(mayhem)
endif()

#===============================================================================
set (CMAKE_SUPPRESS_REGENERATION true)
