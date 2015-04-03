TARGETS = blackjack main

all: $(TARGETS)

blackjack: blackjack.o BJCardDeck.o NDVector.h
	g++ blackjack.o BJCardDeck.o -o blackjack
main: main.o BJCardDeck.o NDVector.h
	g++ main.o BJCardDeck.o -o main

main.o: main.cpp
	g++ -c main.cpp
blackjack.o: blackjack.cpp
	g++ -c blackjack.cpp
BJCardDeck.o: BJCardDeck.cpp NDVector.h
	g++ -c BJCardDeck.cpp

clean:
	rm -f *.o $(TARGETS)
