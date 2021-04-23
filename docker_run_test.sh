#!/bin/bash
docker run --rm -it --name quisp -v "$(pwd):/root/quisp" -u "$(id -u):$(id -g)" quisp /bin/sh -c "cd /root/quisp/test; /bin/bash test.sh"
# docker exec -it quisp /bin/bash
