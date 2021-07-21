#!/bin/bash
set -eu

docker run --rm -it --name quisp -v "$(pwd):/root/quisp" -u "$(id -u):$(id -g)" quisp /bin/sh -c "cd /root/quisp/; make ci"

