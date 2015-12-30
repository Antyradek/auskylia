CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -g -I.
LFLAGS = -lboost_system -lpthread

CMD = $(CXX) $(CXXFLAGS) $(LFLAGS) $^ -o $@

OBJS = Model.o roll.o Path.o 

run: all
	./test

all: test

debug: CXXFLAGS += -DDEBUG
debug: all

test: test.o $(OBJS)
	$(CMD)

clean:
	rm -f *.o

.PHONY: all clean
