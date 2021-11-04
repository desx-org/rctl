# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.202.5/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11/9, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, debian-9, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# [Optional] Uncomment this section to install additional packages.
 RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends ninja-build


RUN git clone https://github.com/Microsoft/vcpkg.git /opt/vcpkg

WORKDIR /opt/vcpkg

RUN ./bootstrap-vcpkg.sh && \
./vcpkg integrate install && \
./vcpkg integrate bash && \
echo 'export PATH=$PATH:/opt/vcpkg' >>~/.bashrc \
echo 'export PATH=$PATH:/opt/vcpkg' >>/home/vscode/.bashrc

