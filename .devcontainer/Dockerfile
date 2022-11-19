FROM ghcr.io/sfc-aqua/quisp-dev:latest

RUN mkdir /var/run/sshd
RUN echo 'root:coffeeplease' | chpasswd
RUN echo 'vscode:morecoffee' | chpasswd
RUN sed -i 's/.*PermitRootLogin.*/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd
ENV NOTVISIBLE "in users profile"
RUN echo "export VISIBLE=now" >> /etc/profile
EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]
