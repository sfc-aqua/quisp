#!/bin/sh
docker run --rm -it --name quisp -v "$(pwd):/root/quisp" -u "$(id -u):$(id -g)" quisp /bin/sh -c "/bin/bash　/root/quisp/test/test.sh"
# docker exec -it quisp /bin/bash