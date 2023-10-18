read-file : read_file.o all clean

read_file.o: read_file.cpp
	g++ -c read_file.cpp

all: 
	g++ read_file.o -o read-file

clean:
	rm *.o
