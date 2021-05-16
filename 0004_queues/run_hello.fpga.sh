#!/bin/bash
. /opt/intel/inteloneapi/setvars.sh
/bin/echo "##" $(whoami) is running xpublog 4 -- Hello SYCL for FPGA - hello.cpp
make run_fpga

