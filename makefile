all: madness
FLAGS = -Wall -Wextra


madness: play.o
		g++ play.o -o bin/madness

play.o: play.cpp parser.h
		g++ -c play.cpp parser.h

clean:
		rm -f *.o bin/madness 