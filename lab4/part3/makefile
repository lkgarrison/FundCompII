all: monkeySort blackjack #testBJCardDeck

monkeySort: monkeySort.o BJCardDeck.o
	g++ monkeySort.o BJCardDeck.o -o monkeySort

blackjack: blackjack.o BJCardDeck.o
	g++ blackjack.o BJCardDeck.o -o blackjack

monkeySort.o: monkeySort.cpp
	g++ -c monkeySort.cpp
blackjack.o: blackjack.cpp
	g++ -c blackjack.cpp
BJCardDeck.o: BJCardDeck.cpp
	g++ -c BJCardDeck.cpp

clean:
	rm -f *.o monkeySort blackjack
