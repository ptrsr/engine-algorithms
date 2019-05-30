
# get the base Ubuntu image from Docker Hub
FROM ubuntu:18.04

# update apps on the base image
RUN apt-get -y update && apt-get install -y

# install dependencies
RUN apt-get -y install git cmake g++

# specify project directory in image
ENV PROJECT_DIR /usr/src/engine-algorithms/

# copy local source files to image
COPY ./ ${PROJECT_DIR}

# create build dir
RUN mkdir ${PROJECT_DIR}/build

# set working directory to build for cmake
WORKDIR ${PROJECT_DIR}/build

# specify build args for cmake
ENV BUILD_ARGS=-DCMAKE_BUILD_TYPE=Release

RUN cmake ${BUILD_ARGS} -DBUILD_HEAD=OFF ..
RUN make -j

WORKDIR ${PROJECT_DIR}/bin

CMD ./tests