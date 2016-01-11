CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -I. -I../controller
LFLAGS = -lboost_system -lpthread

CMD = $(CXX) $(CXXFLAGS) $(LFLAGS) $^ -o $@

OBJS = Model.o roll.o Path.o Graph.o GraphGenerator.o Population.o Strategy.o Node.o ../controller/Command.o

run: all
	./test

fuck: debug 
	gdb ./test

opt: CXXFLAGS += -O3
opt: all

all: test

debug: CXXFLAGS += -DDEBUG -ggdb3
debug: all

test: test.o $(OBJS)
	$(CMD)

clean:
	rm -f *.o
	rm -f test

.PHONY: all clean
