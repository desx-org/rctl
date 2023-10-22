FROM ubuntu:jammy

ARG DEBIAN_FRONTEND=noninteractive DEBIAN_PRIORITY=critical

RUN apt-get update
RUN apt-get install -y build-essential software-properties-common --no-install-recommends clang-tidy ninja-build pkg-config doxygen python3-sphinx clang-format python3-pip lsb-release snapd entr cmake
RUN apt-get clean all

RUN pip install sphinx_rtd_theme && pip install breathe

RUN apt-get install -y git curl zip unzip tar

RUN useradd -ms /bin/bash vscode


RUN mkdir /opt/vcpkg && chmod ugo+rwx /opt/vcpkg

USER vscode
WORKDIR /opt/vcpkg

RUN git clone https://github.com/Microsoft/vcpkg.git .
RUN ./bootstrap-vcpkg.sh
RUN ./vcpkg integrate install
RUN ./vcpkg integrate bash
RUN echo 'export PATH=$PATH:/opt/vcpkg' >>/home/vscode/.bashrc

RUN /opt/vcpkg/vcpkg install fmt catch2

#docker build -t dev_img1 .b

