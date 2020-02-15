#!/bin/sh
DOCKER_BUILDKIT=1 docker build --build-arg VERSION=5.6 -t omnetpp/omnetpp-gui:u18.04-5.6 .