
output: main.o algo.o comp.o start.o
	g++ main.o algo.o comp.o start.o -o output
	
main.o: main.cpp
	g++ -c main.cpp
	
algo.o: algo.cpp comp.h
	g++ -c algo.cpp
	
comp.o: comp.cpp
	g++ -c comp.cpp
	
start.o: start.cpp
	g++ -c start.cpp

clean:
	rm *.o output 
