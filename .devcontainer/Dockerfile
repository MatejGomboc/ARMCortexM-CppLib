FROM debian:12-slim

WORKDIR /root

ENV PATH="/opt/arm-none-eabi-gcc/bin:/opt/cmake/bin:${PATH}"

RUN apt-get update && \
    apt-get install -y wget unzip tar xz-utils llvm-19-tools && \
    rm -rf /var/lib/apt/lists/* && \
    ln -s /usr/bin/FileCheck-19 /usr/bin/filecheck && \
    wget -q https://github.com/ninja-build/ninja/releases/download/v1.13.1/ninja-linux.zip && \
    unzip -q ninja-linux.zip -d /usr/local/bin && \
    rm ninja-linux.zip && \
    wget -q https://github.com/Kitware/CMake/releases/download/v4.1.1/cmake-4.1.1-linux-x86_64.tar.gz && \
    mkdir -p /opt/cmake && \
    tar -xzf cmake-4.1.1-linux-x86_64.tar.gz -C /opt/cmake --strip-components=1 && \
    rm cmake-4.1.1-linux-x86_64.tar.gz && \
    wget -q https://developer.arm.com/-/media/Files/downloads/gnu/14.3.rel1/binrel/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz && \
    mkdir -p /opt/arm-none-eabi-gcc && \
    tar -xf arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz -C /opt/arm-none-eabi-gcc --strip-components=1 && \
    rm arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz
