main.o: main.cpp sphere.h ray.h camera.h hitable.h material.h
	g++ -c main.cpp
material.o: material.cpp
	g++ -c material.cpp
camera.o: camera.cpp
	g++ -c camera.cpp
sphere.o: sphere.cpp
	g++ -c sphere.cpp
main: main.o camera.o sphere.o material.o
	g++ main.o camera.o sphere.o material.o -o main

clean:
	rm -f *.o
	rm -f *.gch


