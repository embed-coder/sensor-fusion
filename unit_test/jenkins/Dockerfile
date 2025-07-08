FROM jenkins/inbound-agent:3309.v27b_9314fd1a_4-1

USER root

# Install required packages and configure passwordless sudo
RUN apt update && apt install -y \
    sudo socat gcc g++ git autogen autoconf \
    build-essential cmake graphviz libgtest-dev libtool pkg-config libserial-dev \
 && apt clean

RUN usermod -aG sudo jenkins && \
    echo "jenkins ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/jenkins && \
    chmod 0440 /etc/sudoers.d/jenkins

# Handle custom certs
RUN mkdir -p /usr/local/share/ca-certificates && \
    chmod -R 777 /usr/local/share/ca-certificates

COPY jenkins-local.crt /usr/local/share/ca-certificates/
RUN update-ca-certificates

USER jenkins