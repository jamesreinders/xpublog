#!/bin/bash
/bin/echo "##" $(whoami) is compiling xpublog 4 -- Hello SYCL for default device - hello.cpp
make
/bin/echo "##" $(whoami) is running xpublog 4 -- Hello SYCL for default device - hello.cpp
make run

