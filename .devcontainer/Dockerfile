FROM debian:12-slim

ENV VCPKG_ROOT=/opt/vcpkg
ENV PATH="${VCPKG_ROOT}:${PATH}"

RUN apt-get update && \
    apt-get install -y curl zip unzip tar git && \
    rm -rf /var/lib/apt/lists/* && \
    git clone --depth 1 --branch 2025.08.27 https://github.com/Microsoft/vcpkg.git /opt/vcpkg && \
    /opt/vcpkg/bootstrap-vcpkg.sh && \
    rm -rf /opt/vcpkg/.git

WORKDIR /root
