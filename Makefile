findcomp: findcomp.o 
	g++ -o findcomp findcomp.cpp --std=c++11
findcomp.o: findcomp.cpp
	g++ -o findcomp.o findcomp.cpp --std=c++11

clean: 
	@rm -f *.o *.run findcomp

run: findcomp
	./findcomp coins.pgm -t 180 -s 3 180 -w out.pgm 


