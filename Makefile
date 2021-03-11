CC = g++
CFLAGS=-std=c++20

SRCS = $(wildcard src/*.cpp)

PROGS = $(patsubst src/%.cpp,exec/%,$(SRCS))


all: $(PROGS)

exec/%: src/%.cpp
	$(CC) $(CFLAGS) -o $@ $<
clean: 
	rm -f $(PROGS)
