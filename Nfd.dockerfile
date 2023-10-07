FROM ubuntu:22.04
USER root

ENV DEBIAN_FRONTEND=interactive

RUN BUILD_DEPS="libpcap-dev libsystemd-dev"\
    apt -y update &&\
    apt -y upgrade &&\
    apt -y install --no-install-recommends \
        $BUILD_DEPS

# install this for add-app-repository
RUN apt -y install software-properties-common

RUN add-apt-repository ppa:named-data/ppa &&\
    apt -y update

RUN apt install nfd
RUN apt install ndn-tools

# echo success on shell starting inside container
RUN echo "success"
RUN systemctl start nfd