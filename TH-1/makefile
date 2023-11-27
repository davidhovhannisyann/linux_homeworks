all: array-summary

array-summary: array-summary.o
	g++ array-summary.o -o array-summary

array-summary.o: array_summary.cpp
	g++ -c array_summary.cpp -o array-summary.o

clean:
	rm *.o 
