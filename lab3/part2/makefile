main: main.o Package.o TwoDayPackage.o OvernightPackage.o
	g++ main.o Package.o TwoDayPackage.o OvernightPackage.o -o main

main.o: main.cpp
	g++ -c main.cpp
Package.o: Package.cpp
	g++ -c Package.cpp
TwoDayPackage.o: TwoDayPackage.cpp
	g++ -c TwoDayPackage.cpp
OvernightPackage.o: OvernightPackage.cpp
	g++ -c OvernightPackage.cpp

clean:
	rm -f *.o main
