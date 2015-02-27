
CXX = g++

BICYCLE_DIR=..

CFLAGS= -g -Wall -std=c++11 
CFLAGS+=-I `root-config --incdir`
CFLAGS+=-I $(BICYCLE_DIR)/include

# CFLAGS+=-O3

BCL_LIB=$(BICYCLE_DIR)/lib/libBicycle.a
# LIBS=-L $(BICYCLE_DIR)/lib -lBicycle 
LIBS=`root-config --libs`  -lm  -lstdc++
TARGET =example1 example2 example3 example4

all: $(TARGET)

example%: example%.o
	#building $@ 
	#deps: $^
	$(CXX) $(CFLAGS) $(LIBS) -o $@ $< $(BCL_LIB)
	strip $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<


clean:
	rm -f $(TARGET) *.o

