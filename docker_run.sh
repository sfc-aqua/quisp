#!/bin/sh
set -eu

if [ -z "${IP-}" ]; then
    IP=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
fi

if [ "$(uname)" = 'Darwin' ]; then

    if [ -z "$DISPLAY" ]; then
        echo "Can't detect X11 display. If you don't know how to resolve this, please check ./doc/xhost_trouble_shooting.md"
        exit 1
    else
        # xterm
        xterm -e "$(xhost "$IP")"
    fi

    socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\""$DISPLAY"\" &
    docker run --privileged --rm -it -v "$(pwd):/root/quisp" -w /root/quisp --name quisp -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY="$IP:0" ghcr.io/sfc-aqua/quisp bash
    trap "lsof -i:6000 -t|xargs kill" 0

elif [ "$(uname -s | cut -c 1-5)" = 'Linux' ]; then

    docker run --privileged --rm -it -v "$(pwd):/root/quisp" -w /root/quisp -u "$(id -u):$(id -g)" --name quisp -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY="$IP:0" ghcr.io/sfc-aqua/quisp bash

else

    echo "Your platform ($(uname -s)) is not supported."
    exit 1

fi
