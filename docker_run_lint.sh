#!/bin/bash
if [ "$TRAVIS" = "true" ]; then
    DIFF=$(git diff --name-only $TRAVIS_COMMIT_RANGE)
    SRCS=$(echo $DIFF | tr " " "\n" | grep 'quisp/.*.cc$' | tr "\n" " ")
    HEADERS=$(echo $DIFF | tr " " "\n" | grep 'quisp/.*.h$' | tr "\n" ",")
    OPTS="-O3 -DNDEBUG=1 -MMD -MP -MF tidy.d -fPIC -Wno-deprecated-register -Wno-unused-function -fno-omit-frame-pointer -DHAVE_SWAPCONTEXT -DXMLPARSER=libxml -DPREFER_QTENV -DWITH_QTENV -DWITH_PARSIM -DWITH_NETBUILDER -DWITH_OSGEARTH -I/usr/include/eigen3 -I./quisp -I/root/omnetpp/include"

    if [ "$SRCS" = "" ]; then 
        echo "no change"
        exit 0
    fi

docker run --rm  -i --name quisp -e TRAVIS -e TRAVIS_COMMIT_RANGE -v "$TRAVIS_BUILD_DIR:/root/quisp" -u "$(id -u):$(id -g)" quisp /bin/sh <<-EOF
    cd /root/quisp
    clang-tidy -warnings-as-errors="*" -header-filter="$HEADERS" $SRCS -- $OPTS
EOF
exit 0
fi

docker run --rm -it --name quisp -v "$(pwd):/root/quisp" -u "$(id -u):$(id -g)" quisp /bin/sh -c "cd /root/quisp/; make ci"

