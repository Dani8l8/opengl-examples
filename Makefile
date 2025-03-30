SRCS := $(wildcard *.cpp)
BINS = $(SRCS:%.cpp=bin/%)

CC=g++
CFLAGS=-Wall -lglut -lGL -lGLU

default: all

bin/%: %.cpp
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm $(BINS)

all: $(BINS)

$(shell mkdir -p bin)
