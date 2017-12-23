CFLAGS = -g

all: DGB

DGB: ./src/*.cpp
	g++ -o DGB -Iinclude ./src/*.cpp -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11
