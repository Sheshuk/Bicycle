
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
ALLTESTS=test_Axis.h test_Array.h test_Table1D.h test_Table2D.h  test_TableIntegrator.h
TARGET =test_all

all: $(TARGET) run

$(TARGET): $(ALLTESTS)

test_%: test_%.o
	#building test $@ 
	#deps: $^
	$(CXX) $(CFLAGS) $(LIBS) -o $@ $< $(BCL_LIB)
	strip $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ -c $<


clean:
	rm $(TARGET)

run: $(TARGET)
	./$(TARGET) --gtest_color=yes

