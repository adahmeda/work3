CC=g++

CPPFLAGS=-std=c++11 -Wall -g

fortes: fortes.cpp
	$(CC) $(CPPFLAGS) fortes.cpp -o fortes -l cgraph

clean:
	-rm -rf fortes
