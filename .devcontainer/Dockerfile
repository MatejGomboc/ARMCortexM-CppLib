FROM debian:12-slim

WORKDIR /root

RUN apt-get update && \
    apt-get install -y wget unzip tar xz-utils llvm-19-tools && \
    rm -rf /var/lib/apt/lists/* && \
    ln -s /usr/bin/FileCheck-19 /usr/local/bin/filecheck && \
    wget -q https://github.com/ninja-build/ninja/releases/download/v1.13.1/ninja-linux.zip && \
    unzip -q ninja-linux.zip -d /usr/local/bin && \
    rm ninja-linux.zip && \
    wget -q https://github.com/Kitware/CMake/releases/download/v4.1.1/cmake-4.1.1-linux-x86_64.tar.gz && \
    mkdir -p /opt/cmake && \
    tar -xzf cmake-4.1.1-linux-x86_64.tar.gz -C /opt/cmake --strip-components=1 && \
    rm cmake-4.1.1-linux-x86_64.tar.gz && \
    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake && \
    ln -s /opt/cmake/bin/ccmake /usr/local/bin/ccmake && \
    ln -s /opt/cmake/bin/cmake-gui /usr/local/bin/cmake-gui && \
    ln -s /opt/cmake/bin/cpack /usr/local/bin/cpack && \
    ln -s /opt/cmake/bin/ctest /usr/local/bin/ctest && \
    wget -q https://developer.arm.com/-/media/Files/downloads/gnu/14.3.rel1/binrel/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz && \
    mkdir -p /opt/arm-none-eabi-gcc && \
    tar -xf arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz -C /opt/arm-none-eabi-gcc --strip-components=1 && \
    rm arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-addr2line /usr/local/bin/arm-none-eabi-addr2line && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-c++filt /usr/local/bin/arm-none-eabi-c++filt && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gcc /usr/local/bin/arm-none-eabi-gcc && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gcc-ranlib /usr/local/bin/arm-none-eabi-gcc-ranlib && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gdb /usr/local/bin/arm-none-eabi-gdb && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gfortran /usr/local/bin/arm-none-eabi-gfortran && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-lto-dump /usr/local/bin/arm-none-eabi-lto-dump && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-ranlib /usr/local/bin/arm-none-eabi-ranlib && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-strip /usr/local/bin/arm-none-eabi-strip && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-ar /usr/local/bin/arm-none-eabi-ar && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-cpp /usr/local/bin/arm-none-eabi-cpp && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gcc-14.3.1 /usr/local/bin/arm-none-eabi-gcc-14.3.1 && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gcov /usr/local/bin/arm-none-eabi-gcov && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gdb-add-index /usr/local/bin/arm-none-eabi-gdb-add-index && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gprof /usr/local/bin/arm-none-eabi-gprof && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-nm /usr/local/bin/arm-none-eabi-nm && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-readelf /usr/local/bin/arm-none-eabi-readelf && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-as /usr/local/bin/arm-none-eabi-as && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-elfedit /usr/local/bin/arm-none-eabi-elfedit && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gcc-ar /usr/local/bin/arm-none-eabi-gcc-ar && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gcov-dump /usr/local/bin/arm-none-eabi-gcov-dump && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gdb-add-index-py /usr/local/bin/arm-none-eabi-gdb-add-index-py && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-ld /usr/local/bin/arm-none-eabi-ld && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-objcopy /usr/local/bin/arm-none-eabi-objcopy && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-size /usr/local/bin/arm-none-eabi-size && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-c++ /usr/local/bin/arm-none-eabi-c++ && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-g++ /usr/local/bin/arm-none-eabi-g++ && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gcc-nm /usr/local/bin/arm-none-eabi-gcc-nm && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gcov-tool /usr/local/bin/arm-none-eabi-gcov-tool && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-gdb-py /usr/local/bin/arm-none-eabi-gdb-py && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-ld.bfd /usr/local/bin/arm-none-eabi-ld.bfd && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-objdump /usr/local/bin/arm-none-eabi-objdump && \
    ln -s /opt/arm-none-eabi-gcc/bin/arm-none-eabi-strings /usr/local/bin/arm-none-eabi-strings
