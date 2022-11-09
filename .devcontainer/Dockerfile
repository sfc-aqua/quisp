FROM ghcr.io/sfc-aqua/quisp:latest


FROM mcr.microsoft.com/devcontainers/base:0-jammy


RUN apt-get update && apt-get install -y --no-install-recommends net-tools iputils-ping openssh-client openssh-server gedit

RUN mkdir /var/run/sshd
RUN echo 'root:coffeeplease' | chpasswd
RUN echo 'vscode:morecoffee' | chpasswd
RUN sed -i 's/.*PermitRootLogin.*/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd
ENV NOTVISIBLE "in users profile"
RUN echo "export VISIBLE=now" >> /etc/profile
EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]


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