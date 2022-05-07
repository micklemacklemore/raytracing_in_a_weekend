main: main.o
	clang++ -std=c++11 -stdlib=libc++ main.o -o main

main.o: main.cpp
	clang++ -std=c++11 -stdlib=libc++ -c main.cpp 

clean:
	rm *.o *.png main