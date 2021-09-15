#!/bin/bash
/bin/echo "##" $(whoami) is compiling xpublog 1 -- Hello SYCL - hello.cpp
make
/bin/echo "##" $(whoami) is running xpublog 1 -- Hello SYCL - hello.cpp
make run

