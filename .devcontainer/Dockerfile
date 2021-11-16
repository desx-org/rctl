# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.202.5/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="ubuntu-21.04"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

RUN apt update
RUN apt install -y software-properties-common --no-install-recommends clang-tidy ninja-build pkg-config doxygen python3-sphinx clang-format python3-pip lsb-release snapd
RUN apt clean all

RUN apt remove -y --purge --auto-remove cmake
ARG CMAKE_VER="3.21.4"
ADD https://github.com/Kitware/CMake/releases/download/v${CMAKE_VER}/cmake-${CMAKE_VER}-linux-x86_64.sh /cmake-${CMAKE_VER}-linux-x86_64.sh
RUN mkdir /opt/cmake
RUN sh /cmake-${CMAKE_VER}-linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN ln -s /opt/cmake/bin/* /usr/local/bin/
RUN cmake --version

RUN pip install sphinx_rtd_theme && pip install breathe 

RUN mkdir /opt/vcpkg && chmod ugo+rwx /opt/vcpkg

WORKDIR /opt/vcpkg

USER vscode 

RUN git clone https://github.com/Microsoft/vcpkg.git .

RUN ./bootstrap-vcpkg.sh && \
./vcpkg integrate install && \
./vcpkg integrate bash && \
echo 'export PATH=$PATH:/opt/vcpkg' >>/home/vscode/.bashrc

RUN /opt/vcpkg/vcpkg install fmt catch2