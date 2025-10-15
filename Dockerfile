FROM ubuntu:24.04

LABEL maintainer="Evgeny Golyshev <eugulixes@gmail.com>"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update \
 && apt install -y \
    build-essential \
    gcc-riscv64-linux-gnu \
    libc6-riscv64-cross \
    make \
    qemu-system-misc \
 && apt clean \
 && rm -rf /var/lib/apt/lists/* \
 && ln -s /usr/riscv64-linux-gnu/lib/ld-linux-riscv64-lp64d.so.1 /lib/ld-linux-riscv64-lp64d.so.1 \
 && ln -s /usr/riscv64-linux-gnu/lib/libc.so.6 /lib/libc.so.6

USER ubuntu

WORKDIR /xv6-riscv
