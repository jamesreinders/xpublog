#!/bin/bash
. /opt/intel/inteloneapi/setvars.sh
/bin/echo "##" $(whoami) is compiling xpublog 4 -- Hello SYCL for FPGA - hello.cpp
make build_fpga

