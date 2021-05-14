#!/bin/bash
. /opt/intel/inteloneapi/setvars.sh
/bin/echo "##" $(whoami) is compiling xpublog 4 -- Hello SYCL for FPGA emulator - hello.cpp
make build_fpga_emu
/bin/echo "##" $(whoami) is running xpublog 4 -- Hello SYCL for FPGA emulator - hello.cpp
make run_fpga_emu

