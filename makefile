CC = g++
CFLAGS = -O3 -std=c++11
mps 	   	: src/mps.cpp
			$(CC) $(CFLAGS) $< -o $@
clean 	   	: mps
			rm -i $<
