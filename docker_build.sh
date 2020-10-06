#!/bin/sh
docker images -a
DOCKER_BUILDKIT=1 docker build --cache-from quisp --build-arg VERSION=5.6 --build-arg GTEST_VERSION=1.10.0 -t quisp .
