#!/bin/sh
docker run --rm -it --name quisp -v "$(pwd):/root/quisp" -u "$(id -u):$(id -g)" quisp /bin/sh -c "sh test.sh;" 