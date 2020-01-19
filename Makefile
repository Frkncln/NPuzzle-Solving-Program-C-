output: hw3.o 
	g++ hw3.o  -o hw3  
main.o: main.cpp
	g++ -c hw3.cpp
	
clean: 
	rm *.o output






