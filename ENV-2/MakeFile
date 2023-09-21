homework: main.o comp_class.o comp_sort.o result clean

main.o: main.cpp
	g++ -c main.cpp

comp_class.o: comp_class.cpp
	g++ -c comp_class.cpp

comp_sort.o: comp_sort.cpp
	g++ -c comp_sort.cpp

result:
	g++ main.o comp_class.o comp_sort.o -o homework

clean:
	rm *.o 
