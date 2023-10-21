manual-append: manual_append.o all clean
manual_append.o: manual_append.cpp
	g++ -c manual_append.cpp
all:
	g++ manual_append.o -o manual-append
clean:
	rm *.o	