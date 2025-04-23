FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt install -y curl gnupg apt-utils apt-transport-https software-properties-common && add-apt-repository ppa:deadsnakes/ppa && apt update && apt install -y  git perl python3.10 python3.10-venv python3.10-dev python3-pip make autoconf g++ flex bison ccache libgoogle-perftools-dev numactl perl-doc libfl2 libfl-dev zlib1g zlib1g-dev autoconf automake autotools-dev libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc git perl python3.8-dev python3-pip rsync libguestfs-tools expat libexpat1-dev libusb-dev libncurses5-dev cmake help2man tcl-dev libreadline-dev jq libexpat-dev device-tree-compiler vim default-jdk default-jre gengetopt patch diffstat texi2html subversion chrpath wget libgtk-3-dev gettext zsh ninja-build clang gtkwave
RUN apt install -y  binutils-dev libelf-dev
RUN wget https://github.com/stnolting/riscv-gcc-prebuilt/releases/download/rv32i-4.0.0/riscv32-unknown-elf.gcc-12.1.0.tar.gz
RUN mkdir /opt/riscv
RUN tar -xzf riscv32-unknown-elf.gcc-12.1.0.tar.gz -C /opt/riscv/
RUN export PATH=$PATH:/opt/riscv/bin
RUN mkdir -p /opt && cd /opt && wget https://github.com/accellera-official/systemc/archive/refs/tags/3.0.1.tar.gz && tar -xvzf 3.0.1.tar.gz && rm 3.0.1.tar.gz && cd systemc-3.0.1 && mkdir objdir && cd objdir && export CXX=g++ && ../configure && make && make install && cd .. && rm -rf objdir
ENV SYSTEMC_HOME=/opt/systemc-3.0.1
ENV LD_LIBRARY_PATH=/opt/systemc-3.0.1/lib-linux64
ENV VERILATOR_SRC=/home/verilator/include
