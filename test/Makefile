
CXX = g++

BICYCLE_DIR=..

CFLAGS= -g -Wall -std=c++11 
CFLAGS+=-I `root-config --incdir`
CFLAGS+=-I $(BICYCLE_DIR)/include

# CFLAGS+=-O3

# LIBS=-L $(BICYCLE_DIR)/lib -lBicycle 
LIBS=-lm  -lstdc++ -lpthread -L /usr/src/gtest -lgtest_main -lgtest
RLIBS=`root-config --libs`
ALLTESTS=$(ls *.h)
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
	rm -f $(TARGET) *.o

run: $(TARGET)
	rm -f report/*.xml
	./$(TARGET) --gtest_color=yes --gtest_output=xml:report/

