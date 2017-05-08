CC=g++

CPPFLAGS=-std=c++11 -Wall

conta-caminhos: conta-caminhos.cpp
	$(CC) $(CPPFLAGS) conta-caminhos.cpp -o conta-caminhos -l cgraph

clean:
	-rm -rf conta-caminhos
