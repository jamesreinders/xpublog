#!/bin/bash
rm -f Assets/EnlightenedNermalWithBook.png
source /opt/intel/oneapi/setvars.sh > /dev/null 2>&1
/bin/echo "##" $(whoami) is compiling xpublog 1 -- Hello SYCL - hello.cpp

LD_LIBRARY_PATH=/opt/intel/openvino/opencv/lib:$LD_LIBRARY_PATH
OPENCV_OPTIONS='-I /opt/intel/openvino/opencv/include/ -L /opt/intel/openvino/opencv/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs'
I_VALUE_QUIET='-ferror-limit=1 -Wno-pass-failed'
dpcpp $OPENCV_OPTIONS $I_VALUE_QUIET lab/hello.cpp -o bin/hello

if [ $? -eq 0 ]; then cd Assets; ../bin/hello; fi



