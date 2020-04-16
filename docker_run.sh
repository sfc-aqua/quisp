#!/bin/sh
IP=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
docker run --rm -it -v "$(pwd):/root/models" -u "$(id -u):$(id -g)" -u=0 -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY="$IP:0" quisp
