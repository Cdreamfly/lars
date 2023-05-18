CXX=g++
CFLASS= -g -O2  -Wall -fPIC -Wno-deprecated

INC=-I../include
LIB=-L../lib -lreactor
OBJS=$(addsuffix .o, $(basename $(wildcard *.cc)))

all:
	$(CXX) -o hello_lars $(CFLASS) hello_lars.cpp $(INC) $(LIB)

clean:
	-rm -rf *.o hello_lars