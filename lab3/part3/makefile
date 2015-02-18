all: demoCreditCard demoPackage

demoCreditCard: demoCreditCard.o BankAccount.o CreditCard.o 
	g++ demoCreditCard.o BankAccount.o CreditCard.o  -o demoCreditCard 
demoPackage: demoPackage.o Package.o TwoDayPackage.o OvernightPackage.o
	g++ -Wall demoPackage.o Package.o TwoDayPackage.o OvernightPackage.o -o demoPackage

demoCreditCard.o: demoCreditCard.cpp
	g++ -c demoCreditCard.cpp
BankAccount.o: BankAccount.cpp 
	g++ -c BankAccount.cpp
CreditCard.o: CreditCard.cpp
	g++ -c CreditCard.cpp

demoPackage.o: demoPackage.cpp
	g++ -Wall -c demoPackage.cpp
Package.o: Package.cpp
	g++ -Wall -c Package.cpp
TwoDayPackage.o: TwoDayPackage.cpp
	g++ -Wall -c TwoDayPackage.cpp
OvernightPackage.o: OvernightPackage.cpp
	g++ -Wall -c OvernightPackage.cpp

clean:
	rm -f *.o demoCreditCard demoPackage
