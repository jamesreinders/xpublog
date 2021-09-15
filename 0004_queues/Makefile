CXX = dpcpp
LDFLAGS =  -tbb -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs
EXE_NAME = hello
SOURCES = lab/hello.cpp
BINDIR = bin
OPENCV_OPTIONS = -I /opt/intel/openvino/opencv/include/ -L /opt/intel/openvino/opencv/lib
TMPFIX = /opt/intel/openvino/deployment_tools/inference_engine/external/tbb/lib
TMPFIXL = -L $(TMPFIX)
CXXFLAGS = $(TMPFIXL) -ferror-limit=1 -Wno-pass-failed $(OPENCV_OPTIONS) $(LDFLAGS)
ME = $(shell eval whoami)
QSUBOPT = -j oe

.PHONY: submit submit_fpga submit_fpga_emu build run build_fpga run_fpga build_fpga_emu run_fpga_emu clean

all: submit_fpga_emu

clean: 
	rm -rf $(BINDIR)/$(EXE_NAME) EnlightenedNermalWithBook.png* NermalWithBook540.jpg
	rm -rf *.o *.d *.out *.mon *.emu *.aocr *.aoco *.prj $(EXE_NAME)*.fpga_emu* $(EXE_NAME)*.fpga *.a *.e[0-9][0-9][0-9][0-9][0-9][0-9] *.o[0-9][0-9][0-9][0-9][0-9][0-9]
	rm -Rf bin/*

submit:
	qsub $(QSUBOPT) -N xpublog4DEF -d . build_and_run_hello.sh

build: $(BINDIR)/$(EXE_NAME)

$(BINDIR)/$(EXE_NAME): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$(EXE_NAME) $(SOURCES)

run: $(BINDIR)/$(EXE_NAME)
	rm -f EnlightenedNermalWithBook.png
	cp -p Assets/NermalWithBook540.jpg .
	LD_LIBRARY_PATH=$(XTRALIB):$(TMPFIX):/opt/intel/openvino_2021/opencv/lib:$(LD_LIBRARY_PATH) $(BINDIR)/$(EXE_NAME)
	cp -p EnlightenedNermalWithBook.png EnlightenedNermalWithBook.png.from_default.png




submit_fpga_emu:
	qsub $(QSUBOPT) -N xpublog4EMU -l nodes=1:fpga_compile:ppn=2 -d . build_and_run_hello.fpga_emu.sh

build_fpga_emu: $(BINDIR)/$(EXE_NAME).fpga_emu

run_fpga_emu: $(BINDIR)/$(EXE_NAME).fpga_emu
	rm -f EnlightenedNermalWithBook.png
	cp -p Assets/NermalWithBook540.jpg .
	LD_LIBRARY_PATH=$(XTRALIB):$(TMPFIX):/opt/intel/openvino_2021/opencv/lib:$(LD_LIBRARY_PATH) $(BINDIR)/$(EXE_NAME).fpga_emu
	cp -p EnlightenedNermalWithBook.png EnlightenedNermalWithBook.png.from_fpga_emu.png

$(BINDIR)/$(EXE_NAME).fpga_emu: $(SOURCES)
	$(CXX) $(CXXFLAGS) -fintelfpga $^ -o $@ -DFPGA_EMULATOR=1



submit_fpga:
	qsub $(QSUBOPT) -N xpublog4CompFPGA -l nodes=1:fpga_compile:ppn=2 -d . build_hello.fpga.sh 1> /tmp/id.$(ME)
	qsub $(QSUBOPT) -N xpublog4RunFPGA -W depend=afterany:`cat /tmp/id.$(ME)` -l nodes=1:fpga:stratix10:ppn=2 -d . run_hello.fpga.sh

submit_fpga2:
	qsub $(QSUBOPT) -N xpublog4CompFPGA -l nodes=1:fpga:stratix10:ppn=2 -d . build_and_run_hello.fpga.sh

submit_fpga_run:
	qsub $(QSUBOPT) -N xpublog4RunFPGA -l nodes=1:fpga:stratix10:ppn=2 -d . run_hello.fpga.sh

build_fpga: $(BINDIR)/$(EXE_NAME).fpga

run_fpga: $(BINDIR)/$(EXE_NAME).fpga
	rm -f EnlightenedNermalWithBook.png
	cp -p Assets/NermalWithBook540.jpg .
	hostname
	date
	./checksys.sh
	LD_LIBRARY_PATH=$(XTRALIB):$(TMPFIX):/opt/intel/openvino_2021/opencv/lib:$(LD_LIBRARY_PATH) $(BINDIR)/$(EXE_NAME).fpga
	date
	cp -p EnlightenedNermalWithBook.png EnlightenedNermalWithBook.png.from_fpga.png

$(BINDIR)/$(EXE_NAME).fpga: $(BINDIR)/$(EXE_NAME).fpga.o
	echo 'starting FPGA build part 2 - place and route for real FPGA - 90 minutes give or take'
	hostname
	date
	./checksys.sh
#	$(CXX) $(CXXFLAGS) -fintelfpga $^ -o $@ -Xshardware
	$(CXX) $(CXXFLAGS) -fintelfpga $^ -o $@ -Xshardware -Xsboard=pac_s10
	date
	echo 'completed FPGA build'

$(BINDIR)/$(EXE_NAME).fpga.ow: $(SOURCES)
	echo 'starting FPGA build - compile'
	hostname
	date
	./checksys.sh
#	$(CXX) $(CXXFLAGS) -fintelfpga -c $^ -o $@ -DFPGA=1
	$(CXX) $(CXXFLAGS) -fintelfpga -c $^ -o $@ -DFPGA=1 -Xsboard=pac_s10
	date
	echo 'completed FPGA compile host code to object'
