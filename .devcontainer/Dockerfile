# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.202.5/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="ubuntu-21.04"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# [Optional] Uncomment this section to install additional packages.
 RUN apt-get update \
     && apt-get -y install --no-install-recommends ninja-build  pkg-config doxygen

RUN apt update
RUN apt install -y software-properties-common lsb-release
RUN apt clean all
RUN apt remove -y --purge --auto-remove cmake
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
RUN apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"
RUN apt update
RUN apt install -y kitware-archive-keyring 
RUN rm /etc/apt/trusted.gpg.d/kitware.gpg
RUN apt update
RUN apt install -y cmake


RUN mkdir /opt/vcpkg && chmod ugo+rwx /opt/vcpkg

WORKDIR /opt/vcpkg

USER vscode 

RUN git clone https://github.com/Microsoft/vcpkg.git .

RUN ./bootstrap-vcpkg.sh && \
./vcpkg integrate install && \
./vcpkg integrate bash && \
echo 'export PATH=$PATH:/opt/vcpkg' >>~/.bashrc \
echo 'export PATH=$PATH:/opt/vcpkg' >>/home/vscode/.bashrc

RUN vcpkg install fmt catch2