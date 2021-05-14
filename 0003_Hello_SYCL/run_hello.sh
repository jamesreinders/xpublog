#!/bin/bash
/bin/echo "##" $(whoami) is compiling xpublog -- Hello SYCL - hello.cpp
make
/bin/echo "##" $(whoami) is running xpublog -- Hello SYCL - hello.cpp
make run

