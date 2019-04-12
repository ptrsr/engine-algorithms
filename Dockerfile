
# Get the base Ubuntu image from Docker Hub
FROM ubuntu:18.04

EXPOSE 80

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# Install the Clang compiler
#RUN apt-get -y install clang

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY ["./", "/usr/src/engine-algorithms/"]

# Specify the working directory
WORKDIR /usr/src/engine-algorithms

# Run bootstrap
# - infinite jobs, do not prompt, headless, test
CMD ["./bootstrap.sh", "-ji", "-y", "-e", "-t"]
