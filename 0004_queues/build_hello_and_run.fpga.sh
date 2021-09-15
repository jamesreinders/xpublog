#!/bin/bash
. /opt/intel/inteloneapi/setvars.sh
/bin/echo "##" $(whoami) is compiling xpublog 4 -- Hello SYCL for FPGA - hello.cpp
make build_fpga
/bin/echo "##" $(whoami) is running xpublog 4 -- Hello SYCL for FPGA - hello.cpp
echo "---aocl diagnose >>>"
aocl diagnose
echo "<<< aocl diagnose---"
find / -name "libopae-c.so" 2>/dev/null
make run_fpga


