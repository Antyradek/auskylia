controllerMain: controllerMain.cpp Controller.cpp ViewServer.cpp Message.cpp XMLParser.cpp
	g++ -std=c++11 -Wall -D_DEBUG -g -o controllerMain controllerMain.cpp Controller.cpp ViewServer.cpp Message.cpp XMLParser.cpp

clean:
	rm -f controllerMain

run: controllerMain
	./controllerMain 8080

all: clean controllerMain run

.PHONY: clean run all
