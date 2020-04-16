#!/bin/sh
IP=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
if [ -z "$DISPLAY" ]
then
    echo "Can't detect X11 display. If you don't know how to resolve this, please check ./doc/xhost_trouble_shooting.md"
    exit 1
else
    # xterm
    xterm -e "$(xhost $IP)"
fi
socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\" &
docker run --rm -it -v "$(pwd):/root/quisp" -u "$(id -u):$(id -g)" --name quisp -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY="$IP:0" quisp
trap "lsof -i:6000 -t|xargs kill" 0


