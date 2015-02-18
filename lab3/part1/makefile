main: main.o BankAccount.o CreditCard.o Savings.o
	g++ main.o BankAccount.o CreditCard.o Savings.o -o main

main.o: main.cpp
	g++ -c main.cpp
BankAccount.o: BankAccount.cpp 
	g++ -c BankAccount.cpp
CreditCard.o: CreditCard.cpp
	g++ -c CreditCard.cpp
Savings.o: Savings.cpp
	g++ -c Savings.cpp

clean:
	rm -f *.o main
