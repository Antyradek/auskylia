CXX=g++
CPPFLAGS=-std=c++11 -Wall -pthread
LFLAGS=-lpthread
DFLAGS=-D_DEBUG -g -Og
#FILES=controllerMain.cpp Controller.cpp ViewServer.cpp Message.cpp XMLParser.cpp
FILES=$(wildcard *.cpp) $(wildcard ../model/*.cpp)
FILES_D=$(filter-out ../model/test.cpp BlockingQueueTests.cpp BlockingQueue.cpp, $(FILES))

-include $(FILES:%.cpp=%.d)

Debug: CPPFLAGS+=$(DFLAGS)
Debug: $(FILES_D:%.cpp=%.o)
	$(CXX) $(CPPFLAGS) $(LFLAGS) -MMD -MP -o bin/Debug/controller $^


controllerMain: controllerMain.cpp Controller.cpp ViewServer.cpp Message.cpp XMLParser.cpp
	g++ -std=c++11 -Wall -D_DEBUG -g -pthread -lpthread -o controllerMain controllerMain.cpp Controller.cpp ViewServer.cpp Message.cpp XMLParser.cpp

clean:
	rm -f controllerMain

cleanDebug:
	rm -f controllerMain
	rm -f *.o
	rm -f *.d
	rm -f ../model/*.o
	rm -f ../model/*.d
	rm -f bin/Debug/*

runDebug: bin/Debug/controller
	./bin/Debug/controller

run: controllerMain
	./controllerMain 8080

all: clean controllerMain run

.PHONY: clean run all cleanDebug runDebug
