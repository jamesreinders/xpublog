#!/bin/bash
. /opt/intel/inteloneapi/setvars.sh
/bin/echo "##" $(whoami) is compiling xpublog 4 -- Hello SYCL for default device - hello.cpp
make build
/bin/echo "##" $(whoami) is running xpublog 4 -- Hello SYCL for default device - hello.cpp
make run

