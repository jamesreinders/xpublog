CXX = dpcpp
CXXFLAGS = -ferror-limit=1 -Wno-pass-failed
LDFLAGS =  -tbb -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs
EXE_NAME = hello
SOURCES = lab/hello.cpp
BINDIR = bin
OPENCV_OPTIONS = -I /opt/intel/openvino/opencv/include/ -L /opt/intel/openvino/opencv/lib
TMPFIX = /opt/intel/openvino/deployment_tools/inference_engine/external/tbb/lib
TMPFIXL = -L $(TMPFIX)

all: main

main:
	$(CXX) $(TMPFIXL) $(CXXFLAGS) $(OPENCV_OPTIONS) $(LDFLAGS) -o $(BINDIR)/$(EXE_NAME) $(SOURCES)

run: 
	rm -f EnlightenedNermalWithBook.png
	cp -p Assets/NermalWithBook540.jpg .
	LD_LIBRARY_PATH=$(TMPFIX):/opt/intel/openvino/opencv/lib:$(LD_LIBRARY_PATH) $(BINDIR)/$(EXE_NAME)

clean: 
	rm -rf $(BINDIR)/$(EXE_NAME) EnlightenedNermalWithBook.png
