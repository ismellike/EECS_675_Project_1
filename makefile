P=battleships

Project: main.o Game.o Player.o Board.o Marker.o PlayerMonitor.o
	g++ -std=c++11 -pthread -g -Wall main.o Game.o Player.o Board.o Marker.o PlayerMonitor.o -o $(P)
	
main.o: main.cpp Game.cpp
	g++ -std=c++11 -g -Wall -c main.cpp
	
Game.o: Game.h Player.cpp Board.cpp
	g++ -std=c++11 -g -Wall -c Game.cpp
	
Player.o: Player.h Board.cpp
	g++ -std=c++11 -g -Wall -c Player.cpp

Board.o: Board.h Marker.cpp
	g++ -std=c++11 -g -Wall -c Board.cpp

Marker.o: Marker.h
	g++ -std=c++11 -g -Wall -c Marker.cpp
	
PlayerMonitor.o: PlayerMonitor.h
	g++ -std=c++11 -g -Wall -c PlayerMonitor.cpp

clean:
	rm *.o $(P)

tar:
	mkdir -p dir$(P)
	cp *.cpp *.h makefile dir$(P)
	tar -cvzf dir$(P).tgz dir$(P)
	-rm -rf dir$(P)
