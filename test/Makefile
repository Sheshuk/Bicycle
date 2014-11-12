
CXX = g++

BICYCLE_DIR=..

CFLAGS= -g -Wall -std=c++11 
CFLAGS+=-I `root-config --incdir`
CFLAGS+=-I $(BICYCLE_DIR)/include

# CFLAGS+=-O3

BCL_LIB=$(BICYCLE_DIR)/lib/libBicycle.a
# LIBS=-L $(BICYCLE_DIR)/lib -lBicycle 
LIBS=`root-config --libs`  -lm  -lstdc++
LIBS+=-lpthread -L /usr/src/gtest -lgtest_main -lgtest 

TARGETS =test_axis test_Flux2D test_FluxIntegrator

all: $(TARGETS) run

test_%: test_%.cpp
	#building test $@ 
	#deps: $^
	$(CXX) $(CFLAGS) $(LIBS) -o $@ $^ $(BCL_LIB)
	strip $@

clean:
	rm $(TARGETS)

run: $(TARGETS)
	$(foreach app,$^,./$(app) --gtest_color=yes;)

