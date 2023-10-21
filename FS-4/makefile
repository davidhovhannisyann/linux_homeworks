redirect-cin: redirect_cin.o all clean

redirect_cin.o: redirect_cin.cpp
	g++ -c redirect_cin.cpp

all:
	g++ redirect_cin.o -o redirect-cin

clean:
	rm *.o