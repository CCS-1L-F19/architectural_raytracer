main.o: main.cpp sphere.h ray.h camera.h hitable.h
	g++ -c main.cpp
camera.o: camera.cpp
	g++ -c camera.cpp
sphere.o: sphere.cpp
	g++ -c sphere.cpp
main: main.o camera.o sphere.o
	g++ main.o camera.o sphere.o -o main

clean:
	rm -f *.o
	rm -f *.gch


