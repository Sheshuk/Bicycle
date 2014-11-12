CXX = g++
CFLAGS= -g -Wall -std=c++11 -fPIC
CFLAGS+=-I `root-config --incdir` -I include/
# CFLAGS+=-O3
GTESTLIBS= -lpthread -L /usr/src/gtest -lgtest -lgtest_main
LIBS=`root-config --libs`  -lm  -lstdc++

OBJ = Axis.o Array1D.o Array2D.o TableReader.o TableIntegrator.o Table1D.o Table2D.o  RootUtils.o
TARGET =TestFlux
TEST_DIR = ./test/
BIN_DIR=./bin/
LIB_DIR=./lib/
OBJECTS=$(addprefix $(BIN_DIR),$(OBJ))

all: libs tests

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
	rm $(BIN_DIR)/* $(LIB_DIR)/*
	(cd test/; $(MAKE) clean)
tests:
	$(MAKE) -C $(TEST_DIR)
