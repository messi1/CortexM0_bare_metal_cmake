FROM ubuntu:23.10 AS baremetal

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

ENV TZ=Europe/Zurich
ENV DEBIAN_FRONTEND=noninteractive 

ENTRYPOINT ["/bin/bash"]
RUN apt update && apt -y upgrade && apt -y install \
    bash \
    bc \
    build-essential \
    clang \
    clang-format \
    clang-tidy \ 
    clangd \
    cmake \
    cpio \
    cppcheck \
    curl \
    docker.io \
    gdb \
    git \
    gperf \
    iputils-ping \
    lcov \
    linux-tools-generic \
    llvm \
    nano \
    ninja-build \
    pkg-config \
    python3 \
    python3-pip \
    rsync \
    unzip \
    wget \
    picocom \
    openocd \
    libusb-1.0-0-dev \
    udev \
    && apt -y autoremove && apt -y autoclean && apt -y clean && exit 0


# Segger cross-platform debugger and performance analyzer for J-Link and J-Trace.
RUN wget --quiet https://www.segger.com/downloads/jlink/Ozone_Linux_x86_64.deb && \
    apt -y install ./Ozone_Linux_x86_64.deb

# Segger command line tools
RUN wget --quiet --post-data="accept_license_agreement=accepted" https://www.segger.com/downloads/jlink/JLink_Linux_x86_64.deb && \
    apt -y install ./JLink_Linux_x86_64.deb

# STLink is an open source toolset to program and debug STM32 device
RUN mkdir stm32 && cd stm32 && \
    git clone https://github.com/stlink-org/stlink && \
    mkdir build-stlink && cd build-stlink && \
    cmake ../stlink && \
    make && make install && \
    cp ../stlink/config/udev/rules.d/49-stlinkv* /etc/udev/rules.d/

# Gcc toolchain for ARM based processors
RUN wget --quiet https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2 && \
    tar xvf gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2 -C /usr/local
ENV PATH=/usr/local/gcc-arm-none-eabi-9-2020-q2-update/bin


RUN mkdir -p /home/workspace && chmod 777 /home /home/workspace
RUN groupadd --gid $USER_GID $USERNAME && \
    useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME
