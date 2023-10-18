read-file : read_file.o result clean

read_file.o: read_file.cpp
	g++ -c read_file.cpp

result: 
	g++ read_file.o -o read-file

clean:
	rm *.o
