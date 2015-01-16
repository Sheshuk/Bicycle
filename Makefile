CXX = g++
CFLAGS= -g -Wall -std=c++11 -fPIC
CFLAGS+=-I `root-config --incdir` -I include/
# CFLAGS+=-O3
GTESTLIBS= -lpthread -L /usr/src/gtest -lgtest -lgtest_main
LIBS=`root-config --libs`  -lm  -lstdc++

OBJ = Axis.o Interpolator.o ArrayT.o TableT.o
OBJ_R = Array1D.o Array2D.o TableFactory.o TableIntegrator.o Table1D.o Table2D.o  RootUtils.o
TARGET =TestFlux

BYCICLE_DIR=$(shell pwd)
TEST_DIR = $(BYCICLE_DIR)/test/
EXMPL_DIR= $(BYCICLE_DIR)/example/
BIN_DIR=$(BYCICLE_DIR)/bin/
INC_DIR=$(BYCICLE_DIR)/include/
LIB_DIR=$(BYCICLE_DIR)/lib/
OBJECTS=$(addprefix $(BIN_DIR),$(OBJ))

all: libs examples tests

$(TARGET): $(OBJECTS) bin/main.o
	#building APP $@ 
	#deps: $^
	$(CXX) $(CFLAGS) $(LIBS) -o $@ $^
	strip $@
libs: $(LIB_DIR)libBicycle.so $(LIB_DIR)libBicycle.a

$(LIB_DIR)libBicycle.so: $(OBJECTS)
	$(CXX)  -shared -o $@ $^

$(LIB_DIR)libBicycle.a: $(OBJECTS)
	ar rcs $@ $^

$(BIN_DIR)%.o: src/%.cpp
	$(CXX) $(CFLAGS) -o $@ -c $^

obj: $(OBJECTS)


clean:
	rm -f $(BIN_DIR)/* $(LIB_DIR)/*
	(cd $(TEST_DIR);  $(MAKE) clean)
	(cd $(EXMPL_DIR); $(MAKE) clean)
tests:
	$(MAKE) -C $(TEST_DIR)

examples:
	#making $@
	$(MAKE) -C $(EXMPL_DIR)

install: 
	ln -s $(LIB_DIR)/libBicycle.so /usr/lib/
	ln -s $(INC_DIR)  /usr/include/Bicycle

uninstall:
	rm /usr/include/Bicycle
	rm /usr/lib/libBicycle.so
