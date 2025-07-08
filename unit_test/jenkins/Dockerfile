FROM jenkins/inbound-agent:3309.v27b_9314fd1a_4-1

USER root
RUN apt update && apt install -y \
    gcc g++ git autogen autoconf \
    build-essential cmake graphviz \
    libgtest-dev libtool pkg-config \
    libserial-dev \
 && apt clean

# Create a new writable cert directory
RUN mkdir -p /usr/local/share/ca-certificates && \
    chmod -R 777 /usr/local/share/ca-certificates

COPY jenkins-local.crt /usr/local/share/ca-certificates/

# Update certs to a new writable output
RUN update-ca-certificates

USER jenkins