FROM ghcr.io/sfc-aqua/quisp:latest


FROM mcr.microsoft.com/devcontainers/base:0-jammy

COPY --from=0 /root/omnetpp /usr/local/share/omnetpp

ARG DEBIAN_FRONTEND=noninteractive
ARG LLVM_VERSION=13
ARG OMNETPP_VERSION=6.0.1
ARG PYTHON_VERSION=3.9
WORKDIR /root
RUN wget https://raw.githubusercontent.com/sfc-aqua/omnetpp-dockerfiles/main/install.sh && chmod +x /root/install.sh && /root/install.sh dev
RUN chmod -R 775 /usr/local/share/omnetpp
RUN chown -R vscode /usr/local/share/omnetpp

ENV QT_SELECT=5
ENV OMNETPP_RELEASE=omnetpp-6.0
ENV __omnetpp_root_dir=/usr/local/share/omnetpp
ENV QT_LOGGING_RULES=*.debug=false;qt.qpa.*=false
ENV PYTHONPATH=/usr/local/share/omnetpp/python
ENV PATH=/usr/local/share/omnetpp/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin:/root/.local/bin
ENV LD_LIBRARY_PATH=/usr/local/share/omnetpp/lib