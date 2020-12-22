# M/M/1 queuing model implementation using C++
## On Linux
To install a C++ compiler on Linux , type the following inside the terminal:

	sudo apt-get install build-essential


To compile the C++ source file source.cpp, we type:

	g++ mm1.cpp


This command will produce an executable with the default name of a.out. To run the executable file, type:

	./a.out


To compile for a C++11 standard, we add the -std=c++11 flag:

	g++ -std=c++11 mm1.cpp


To enable warnings, we add the -Wall flag:

	g++ -std=c++11 -Wall mm1.cpp


To produce a custom executable name, we add the -o flag followed by an executable name:

	g++ -std=c++11 -Wall mm1.cpp -o myexe


To run the executable fiel:
	
	./myexe
