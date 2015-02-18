blackjack: blackjack.o BJCardDeck.o
	g++ blackjack.o BJCardDeck.o -o blackjack

blackjack.o: blackjack.cpp
	g++ -c blackjack.cpp
BJCardDeck.o: BJCardDeck.cpp
	g++ -c BJCardDeck.cpp

clean:
	rm -f *.o monkeySort blackjack
