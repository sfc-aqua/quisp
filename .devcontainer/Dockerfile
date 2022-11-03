FROM ghcr.io/sfc-aqua/quisp:latest


FROM mcr.microsoft.com/devcontainers/base:0-jammy

COPY --from=0 /root/omnetpp /root/omnetpp

ARG DEBIAN_FRONTEND=noninteractive
ARG LLVM_VERSION=13
ARG OMNETPP_VERSION=6.0.1
ARG PYTHON_VERSION=3.9
WORKDIR /root
RUN wget https://raw.githubusercontent.com/sfc-aqua/omnetpp-dockerfiles/main/install.sh && chmod +x /root/install.sh && /root/install.sh dev

ENV QT_SELECT=5
ENV OMNETPP_RELEASE=omnetpp-6.0
ENV __omnetpp_root_dir=/root/omnetpp
ENV QT_LOGGING_RULES=*.debug=false;qt.qpa.*=false
ENV PYTHONPATH=/root/omnetpp/python
ENV PATH=/root/omnetpp/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin:/root/.local/bin
