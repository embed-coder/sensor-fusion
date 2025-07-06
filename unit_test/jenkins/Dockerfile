FROM jenkins/inbound-agent:3309.v27b_9314fd1a_4-1

USER root
RUN apt update && apt install -y \
    gcc g++ git autogen autoconf \
    build-essential cmake graphviz \
    libgtest-dev libtool pkg-config \
    libserial-dev \
 && apt clean

USER jenkins