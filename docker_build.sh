#!/bin/sh
DOCKER_BUILDKIT=1 docker build --build-arg VERSION=5.6 --build-arg GTEST_VERSION=1.10.0 -t quisp .