FROM debian:stable-slim as builder


RUN \
  apt-get update && \
  apt-get install -y build-essential llvm cmake clang


COPY . /AudioFile
RUN mkdir -p /AudioFile/build
WORKDIR /AudioFile/build

RUN cmake -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF -DCMAKE_CXX_STANDARD=20 -DAUDIO_FILE_BUILD_FUZZER=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
RUN cmake --build .

FROM --platform=linux/amd64 ubuntu:22.04
COPY --from=builder /AudioFile/build/mayhem/testsuite/ /testsuite
COPY --from=builder /AudioFile/build/mayhem/AudioFile_fuzz /AudioFile_fuzz

ENTRYPOINT []
CMD ["/AudioFile_fuzz"]