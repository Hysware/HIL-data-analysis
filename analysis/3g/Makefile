### Makefile --- 
## 
## Description: 
## Author: Hongyi Wu(吴鸿毅)
## Email: wuhongyi@qq.com 
## Created: 日 10月  2 19:40:07 2016 (+0800)
## Last-Updated: 四 10月 21 14:08:10 2021 (+0800)
##           By: Hongyi Wu(吴鸿毅)
##     Update #: 9
## URL: http://wuhongyi.cn 

OBJ = root2matrix
sourcefile = main.cc cube.hh cube.cc sort-hil.hh sort-hil.cc UserDefine.hh

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs) -lSpectrum

CFLAGS = -g -Wall -O2 -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64

GXX = g++ 

all:$(OBJ)

$(OBJ): $(sourcefile)
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) -o $@ $(filter %.cc ,$(sourcefile)) $(ROOTLIBS)

clean:
	rm -f *~ *.o $(OBJ)


######################################################################
### Makefile ends here
