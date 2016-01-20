CXX = g++
CPPFLAGS= -std=c++11 -Wall -pthread
LFLAGS = -lpthread
FILES = $(wildcard controller/*.cpp) $(wildcard model/*.cpp)
EXEC = auskylia

-include $(FILES:%.cpp=%.d)


controllerMain: controllerMain.cpp Controller.cpp ViewServer.cpp Message.cpp XMLParser.cpp
	g++ -std=c++11 -Wall -D_DEBUG -g -pthread -lpthread -o controllerMain controllerMain.cpp Controller.cpp ViewServer.cpp Message.cpp XMLParser.cpp

clean:
	rm -f $(EXEC)
	rm -f controller/*.o
	rm -f controller/*.d
	rm -f model/*.o
	rm -f model/*.d

Release: CPPFLAGS+=-O3
Release: $(FILES_D:%.cpp=%.o)
	$(CXX) $(CPPFLAGS) $(LFLAGS) -MMD -MP -o $(EXEC) $^


all: clean

.PHONY: clean
