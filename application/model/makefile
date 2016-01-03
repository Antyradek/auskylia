CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -g -I.
LFLAGS = -lboost_system -lpthread

CMD = $(CXX) $(CXXFLAGS) $(LFLAGS) $^ -o $@

OBJS = Model.o roll.o Path.o Graph.o GraphGenerator.o Population.o Strategy.o Node.o 

run: all
	./test

fuck: debug 
	gdb ./test

all: test

debug: CXXFLAGS += -DDEBUG
debug: all

test: test.o $(OBJS)
	$(CMD)

clean:
	rm -f *.o

.PHONY: all clean
