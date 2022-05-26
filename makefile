main: main.o
	clang++ -std=c++11 -stdlib=libc++ main.o -o main

main.o: main.cpp
	clang++ -std=c++11 -stdlib=libc++ -c main.cpp 

clean:
	rm *.o ./images/*.png main

video:
	ffmpeg -i images/image%03d.png -c:v libx264 -vf fps=24 -pix_fmt yuv420p out.mp4

run:
	make && ./main
