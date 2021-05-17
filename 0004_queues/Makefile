CXX = dpcpp
LDFLAGS =  -tbb -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs
EXE_NAME = hello
SOURCES = lab/hello.cpp
BINDIR = bin
OPENCV_OPTIONS = -I /opt/intel/openvino_2021/opencv/include/ -L /opt/intel/openvino_2021/opencv/lib
TMPFIX = /opt/intel/openvino_2021/deployment_tools/inference_engine/external/tbb/lib
TMPFIXL = -L $(TMPFIX)
CXXFLAGS = $(TMPFIXL) -ferror-limit=1 -Wno-pass-failed $(OPENCV_OPTIONS) $(LDFLAGS)
ME = $(shell eval whoami)


.PHONY: submit submit_fpga submit_fpga_emu build run build_fpga run_fpga build_fpga_emu run_fpga_emu clean

def: build


submit_all: submit submit_fpga submit_fpga_emu




submit:
	qsub -N xpublog4DEF -d . build_and_run_hello.sh

build: $(BINDIR)/$(EXE_NAME)

$(BINDIR)/$(EXE_NAME): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$(EXE_NAME) $(SOURCES)

run: $(BINDIR)/$(EXE_NAME)
	rm -f EnlightenedNermalWithBook.png
	cp -p Assets/NermalWithBook540.jpg .
	LD_LIBRARY_PATH=$(TMPFIX):/opt/intel/openvino_2021/opencv/lib:$(LD_LIBRARY_PATH) $(BINDIR)/$(EXE_NAME)
	cp -p EnlightenedNermalWithBook.png EnlightenedNermalWithBook.png.from_default.png




submit_fpga_emu:
	qsub -N xpublog4EMU -l nodes=1:fpga_compile:ppn=2 -d . build_and_run_hello.fpga_emu.sh

build_fpga_emu: $(BINDIR)/$(EXE_NAME).fpga_emu

run_fpga_emu: $(BINDIR)/$(EXE_NAME).fpga_emu
	rm -f EnlightenedNermalWithBook.png
	cp -p Assets/NermalWithBook540.jpg .
	LD_LIBRARY_PATH=$(TMPFIX):/opt/intel/openvino_2021/opencv/lib:$(LD_LIBRARY_PATH) $(BINDIR)/$(EXE_NAME).fpga_emu
	cp -p EnlightenedNermalWithBook.png EnlightenedNermalWithBook.png.from_fpga_emu.png

$(BINDIR)/$(EXE_NAME).fpga_emu: $(SOURCES)
	$(CXX) $(CXXFLAGS) -fintelfpga $^ -o $@ -DFPGA_EMULATOR=1



submit_fpga:
	qsub -N xpublog4CompFPGA -l nodes=1:fpga_compile:ppn=2 -d . build_hello.fpga.sh 1> /tmp/id.$(ME)
	qsub -N xpublog4RunFPGA -W depend=afterany:`cat /tmp/id.$(ME)` -l nodes=1:fpga:ppn=2 -d . run_hello.fpga.sh;

build_fpga: $(BINDIR)/$(EXE_NAME).fpga

run_fpga: $(BINDIR)/$(EXE_NAME).fpga
	rm -f EnlightenedNermalWithBook.png
	cp -p Assets/NermalWithBook540.jpg .
	LD_LIBRARY_PATH=$(TMPFIX):/opt/intel/openvino_2021/opencv/lib:$(LD_LIBRARY_PATH) $(BINDIR)/$(EXE_NAME).fpga
	cp -p EnlightenedNermalWithBook.png EnlightenedNermalWithBook.png.from_fpga.png

$(BINDIR)/$(EXE_NAME).fpga: $(BINDIR)/$(EXE_NAME).fpga.o
	echo 'starting FPGA build'
	hostname
	date
	./checksys.sh
	$(CXX) $(CXXFLAGS) -fintelfpga $^ -o $@ -Xshardware
	date
	echo 'completed FPGA build'

$(BINDIR)/$(EXE_NAME).fpga.o: $(SOURCES)
	echo 'starting FPGA run'
	hostname
	date
	./checksys.sh
	$(CXX) $(CXXFLAGS) -fintelfpga -c $^ -o $@ -DFPGA=1
	date
	echo 'completed FPGA run'

clean: 
	rm -rf $(BINDIR)/$(EXE_NAME) EnlightenedNermalWithBook.png* NermalWithBook540.jpg
	rm -rf *.o *.d *.out *.mon *.emu *.aocr *.aoco *.prj $(EXE_NAME)*.fpga_emu* $(EXE_NAME)*.fpga *.a *.sh.e[0-9]* *.sh.o[0-9]*
	rm -Rf bin/*
