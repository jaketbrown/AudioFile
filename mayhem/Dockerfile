FROM debian:stable-slim as builder

COPY . /AudioFile
RUN mkdir -p /AudioFile/build
WORKDIR /AudioFile/build/

RUN \
  apt-get update && \
  apt-get install -y build-essential llvm cmake clang

ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

RUN cmake ../mayhem

#RUN clang++ /AudioFile/mayhem/AudioFile_fuzz.cpp -I/AudioFile -fsanitize=fuzzer,address -o /AudioFile_fuzz

#FROM debian:stable-slim as package
#COPY --from=builder /install /install
#COPY --from=builder /fuzz /fuzz_boxInt