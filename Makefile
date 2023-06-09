TARGET=lib/libreactor.a
CXX=g++
CFLASS=-std=c++11 -g -O2  -Wall -fPIC

SRC=./src
INC=-I./include
OBJS=$(addsuffix .o, $(basename $(wildcard $(SRC)/*.cpp)))

$(TARGET): $(OBJS)
	mkdir -p lib
	ar cqs $@ $^
	-rm -rf src/*.o

%.o:%.cpp
	$(CXX) $(CFLASS) -c -o $@ $< $(INC)


.PHONY: clean

clean:
	-rm -rf src/*.o $(TARGET)