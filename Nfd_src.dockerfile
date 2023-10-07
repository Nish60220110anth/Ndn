FROM --platform=amd64 ubuntu:22.04
USER root

ENV DEBIAN_FRONTEND=interactive

# install git
RUN apt-get -y update &&\
    apt-get -y upgrade &&\
    apt-get -y install git

# download sources
RUN git clone https://github.com/named-data/ndn-cxx.git && \
    git clone --recursive https://github.com/named-data/NFD.git

RUN apt-get install -y pkg-config

# download dependencies for ndn-cxx and install ndn-cxx
RUN BUILD_DEPS="\
    build-essential \
    python3-minimal \
    libboost-all-dev \
    libssl-dev \
    libsqlite3-dev" && \
    apt-get install -y $BUILD_DEPS && \
    cd ./ndn-cxx && \
    ./waf configure &&\
    ./waf &&\
    ./waf install

# download other dependencies for NFD and install NFD
RUN apt-get install -y libpcap-dev libsystemd-dev

RUN cd ./NFD && \
    ./waf configure &&\
    ./waf &&\
    ./waf install

RUN apt-get update && \
      apt-get -y install sudo

# to expose shared libraries to the system
RUN ldconfig

# copy NFD configuration file
RUN cp /usr/local/etc/ndn/nfd.conf.sample /usr/local/etc/ndn/nfd.conf

# copy source code to test NFD
RUN mkdir scratch
WORKDIR /scratch
ADD ./scratch/ .
COPY ./Compile.sh .

# print all contents in the present directory

ENTRYPOINT ["sh","Compile.sh"]