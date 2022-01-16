.PHONY: all clean

SOURCES := $(wildcard *.cpp)
OBJS := $(SOURCES:.cpp=.o)

CC = g++
CFLAGS = -std=c++14
INCLUDES = -I/usr/local/boost/boost_1_78_0
LDFLAGS = -lpthread -lboost_unit_test_framework

all: test_ts_deque
	@echo Done building main

test_ts_deque: $(OBJS)
	$(CC) -o $@ $< $(LDFLAGS)


.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm -f *.o test_ts_deque