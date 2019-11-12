CFLAGS = -Wall -Wextra -DDEBUG -g -pedantic -std=c++14

M = main

$(M): $(M).o
	g++ $(CFLAGS) -o $(M) $(M).o

$(M).o: $(M).cpp HTHeader.h 
	g++ $(CFLAGS) -c $(M).cpp -o $(M).o


all: $(M)

run: all
	./$(M)


checkmem: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(M)

clean:
	rm -f $(M).o
	rm -f $(M)
