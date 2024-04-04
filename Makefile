build:
	g++ -std=c++11 -w piece.cpp board.cpp -o game
	./game 4 4 4 4 2 5 2 3 5 4 1 1 5 2 2 2 5 5 0

clean:
	rm game