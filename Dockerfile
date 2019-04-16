# https://solarianprogrammer.com/2018/05/06/building-gcc-cross-compiler-raspberry-pi/

# Ubuntu 18.04 at the time of writing (2019-04-02)
FROM ubuntu:latest

# Install some tools and compilers + clean up
RUN apt-get update && \
    apt-get install -y git wget \
                       gcc-8 g++-8 cmake bzip2 \
                       gawk bison python3 && \
    apt-get clean autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

# Use GCC 8 as the default
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 999 \
 && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 999 \
 && update-alternatives --install /usr/bin/cc  cc  /usr/bin/gcc-8 999 \
 && update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-8 999

# Add a user called `develop`
RUN useradd -ms /bin/bash develop
RUN echo "develop   ALL=(ALL:ALL) ALL" >> /etc/sudoers

WORKDIR /home/develop

# Download and extract GCC
RUN wget https://ftp.gnu.org/gnu/gcc/gcc-8.3.0/gcc-8.3.0.tar.xz && \
    tar xf gcc-8.3.0.tar.xz && \
    rm gcc-8.3.0.tar.xz
# Download and extract LibC
RUN wget https://ftp.gnu.org/gnu/libc/glibc-2.29.tar.bz2 && \
    tar xjf glibc-2.29.tar.bz2 && \
    rm glibc-2.29.tar.bz2
# Download and extract BinUtils
RUN wget https://ftp.gnu.org/gnu/binutils/binutils-2.32.tar.bz2 && \
    tar xjf binutils-2.32.tar.bz2 && \
    rm binutils-2.32.tar.bz2
# Download the GCC prerequisites
RUN cd gcc-8.3.0 && contrib/download_prerequisites && rm *.tar.*

# Download and install the Linux headers
WORKDIR /home/develop
RUN wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.4.tar.xz
RUN tar xf linux-4.4.tar.xz && rm linux-4.4.tar.xz
WORKDIR /home/develop/linux-4.4
ENV KERNEL=kernel7
RUN make ARCH=arm INSTALL_HDR_PATH=/opt/cross-gcc/arm-linux-gnueabihf headers_install

RUN mkdir -p /opt/cross-gcc

# Build BinUtils
WORKDIR /home/develop/build-binutils
RUN ../binutils-2.32/configure \
        --prefix=/opt/cross-gcc \
        --build=$MACHTYPE --host=$MACHTYPE --target=arm-linux-gnueabihf \
        --with-cpu=cortex-a9 --with-fpu=neon-vfpv3 --with-float=hard \
        --disable-multilib
RUN bash -c 'make -j$[$(nproc) * 2]'
RUN make install

# Build the first part of GCC
WORKDIR /home/develop/build-gcc
RUN ln -s /opt/cross-gcc/arm-linux-gnueabihf /opt/cross-gcc/arm-linux-gnueabihf/usr
RUN ../gcc-8.3.0/configure \
        --prefix=/opt/cross-gcc \
        --build=$MACHTYPE --host=$MACHTYPE --target=arm-linux-gnueabihf \
        --with-cpu=cortex-a9 --with-fpu=neon-vfpv3 --with-float=hard \
        --enable-languages=c,c++,fortran \
        --disable-multilib 
RUN bash -c 'make -j$[$(nproc) * 2] all-gcc'
RUN make install-gcc
ENV PATH=/opt/cross-gcc/bin:${PATH}

# Build GLIBC
WORKDIR /home/develop/build-glibc
        # --with-cpu=cortex-a9 \
        # --with-binutils=/opt/cross-gcc/binutils \
RUN ../glibc-2.29/configure \
        --prefix=/opt/cross-gcc/arm-linux-gnueabihf \
        --build=$MACHTYPE --host=arm-linux-gnueabihf --target=arm-linux-gnueabihf \
        --with-arch=armv7-a --with-fpu=neon-vfpv3 --with-float=hard \
        --with-tune=cortex-a9 \
        --with-headers=/opt/cross-gcc/arm-linux-gnueabihf/include \
        --enable-kernel=4.4.0 \
        --disable-multilib \
        libc_cv_forced_unwind=yes
RUN make install-bootstrap-headers=yes install-headers
RUN bash -c 'make -j$[$(nproc) * 2] csu/subdir_lib'
RUN install csu/crt1.o csu/crti.o csu/crtn.o /opt/cross-gcc/arm-linux-gnueabihf/lib
RUN arm-linux-gnueabihf-gcc -nostdlib -nostartfiles -shared -x c /dev/null \
        -o /opt/cross-gcc/arm-linux-gnueabihf/lib/libc.so
RUN touch /opt/cross-gcc/arm-linux-gnueabihf/include/gnu/stubs.h

# Continue building GCC
WORKDIR /home/develop/build-gcc
RUN bash -c 'make -j$[$(nproc) * 2] all-target-libgcc'
RUN make install-target-libgcc

# Finish building GLIBC
WORKDIR /home/develop/build-glibc
RUN bash -c 'make -j$[$(nproc) * 2]'
RUN make install

# Finish building GCC
WORKDIR /home/develop/build-gcc
RUN bash -c 'make -j$[$(nproc) * 2]'
RUN make install

################################################################################

# for gdbserver
EXPOSE 2000

WORKDIR /home/develop
RUN git clone https://github.com/google/googletest.git

USER develop

ARG WORKSPACE_ROOT
ENV WORKSPACE_ROOT=${WORKSPACE_ROOT}
VOLUME ${WORKSPACE_ROOT}
WORKDIR ${WORKSPACE_ROOT}/build