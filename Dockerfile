FROM ubuntu:20.04 as base
ARG DEBIAN_FRONTEND=noninteractive
RUN apt update -y && apt install -y --no-install-recommends \
    qt5-default libqt5opengl5-dev libgtk-3-0 default-jre osgearth \
    libeigen3-dev cmake g++ gdb gpg-agent software-properties-common wget \
    vim bison flex make lld-12 git clang-format-12 clang-tidy-12 lldb-12 pip && \
    ln -s /usr/bin/clang-format-12 /usr/bin/clang-format && \
    ln -s /usr/bin/clang-tidy-12 /usr/bin/clang-tidy && \
    ln -sf /usr/bin/clang-12 /usr/bin/clang && \
    ln -sf /usr/bin/clang++-12 /usr/bin/clang++ && \
    ln -sf /usr/bin/llvm-profdata-12 /usr/bin/llvm-profdata && \
    ln -sf /usr/bin/llvm-cov-12 /usr/bin/llvm-cov && \
    ln -sf /usr/bin/lld-12 /usr/bin/lld

# first stage - build OMNeT++ with GUI
FROM base as builder

ARG VERSION
WORKDIR /root
RUN wget https://github.com/omnetpp/omnetpp/releases/download/omnetpp-$VERSION/omnetpp-$VERSION-linux-x86_64.tgz \
    --referer=https://omnetpp.org/ -O omnetpp-src-linux.tgz --progress=dot:giga && \
    tar xf omnetpp-src-linux.tgz && rm omnetpp-src-linux.tgz
RUN mv omnetpp-$VERSION omnetpp
WORKDIR /root/omnetpp
ENV PATH /root/omnetpp/bin:$PATH

RUN bash -c "source setenv && ./configure WITH_OSG=no && \
    make -j $(nproc) MODE=debug base && \
    make -j $(nproc) MODE=release base && \
    rm -r doc out test samples config.log config.status"

# second stage - copy only the final binaries (to get rid of the 'out' folder and reduce the image size)
FROM base
ARG VERSION
RUN mkdir -p /root/omnetpp
WORKDIR /root/omnetpp
COPY --from=builder /root/omnetpp/ .
ENV PATH /root/omnetpp/bin:$PATH
RUN chmod 775 /root/ && \
    mkdir -p /root/quisp && \
    chmod 775 /root/quisp && \
    touch ide/error.log && chmod 666 ide/error.log && \
    mv bin/omnetpp bin/omnetpp.bak && \
    sed 's!$IDEDIR/../samples!/root/quisp!' bin/omnetpp.bak >bin/omnetpp && \
    rm bin/omnetpp.bak && chmod +x bin/omnetpp && \
    echo 'PS1="quisp:\w\$ "' >> /root/.bashrc && chmod +x /root/.bashrc && \
    touch /root/.hushlogin

RUN apt remove -y python3.8 && \
    apt install -y python3.9 python3.9-distutils curl time && \
    curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && \
    python3.9 get-pip.py && \
    rm get-pip.py && \
    ln -s /usr/bin/python3.9  /usr/local/bin/python

ENV HOME=/root/
CMD /bin/bash --init-file /root/.bashrc
WORKDIR /root/quisp
