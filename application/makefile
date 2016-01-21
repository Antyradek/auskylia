CXX = g++
CPPFLAGS= --std=c++11 -Wall -pthread
LFLAGS = -lpthread
FILES_ALL = $(wildcard controller/*.cpp) $(wildcard model/*.cpp)
FILES=$(filter-out model/test.cpp controller/BlockingQueueTests.cpp controller/BlockingQueue.cpp, $(FILES_ALL))
EXEC = auskylia

all: $(EXEC)

$(EXEC): CPPFLAGS+=-O3
$(EXEC): $(FILES:%.cpp=%.o)
	$(CXX) $(CPPFLAGS) $(LFLAGS) -MMD -MP -o $(EXEC) $^


.PHONY: clean

clean:
	rm -f $(EXEC)
	rm -f controller/*.o
	rm -f controller/*.d
	rm -f model/*.o
	rm -f model/*.d