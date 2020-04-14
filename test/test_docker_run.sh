#!/bin/sh
docker run --rm -it --name quisp -v "$(pwd):/root/quisp" -u "$(id -u):$(id -g)" /bin/sh -c "sh /test/test.sh" quisp