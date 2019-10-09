main: main.o ray.o camera.o hitable.o sphere.o
	g++ main.cpp -o main
main.o: main.cpp
	g++ -c main.cpp
camera.o: camera.h
	g++ -c camera.h
ray.o: ray.h
	g++ -c ray.h
hitable.o: hitable.h
	g++ -c hitable.h
sphere.o: sphere.h
	g++ -c sphere.h

