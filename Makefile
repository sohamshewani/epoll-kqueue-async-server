CC=g++
CFLAGS=-Wall -std=c++11 -g
SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:.cpp=.o)
EXEC=epoll-kqueue-async-server

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXEC)
