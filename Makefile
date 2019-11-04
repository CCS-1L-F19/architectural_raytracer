
CXX = g++

CXXFLAGS = -Wall -Wextra -g

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp 
material.o: material.cpp
	${CXX} ${CXXFLAGS} -c material.cpp
camera.o: camera.cpp
	${CXX} ${CXXFLAGS} -c camera.cpp
sphere.o: sphere.cpp
	${CXX} ${CXXFLAGS} -c sphere.cpp
bounding_box.o: bounding_box.cpp
	${CXX} ${CXXFLAGS} -c bounding_box.cpp
BVH.o: BVH.cpp
	${CXX} ${CXXFLAGS} -c BVH.cpp
main: main.o camera.o sphere.o material.o bounding_box.o BVH.o
	g++ -g $^ -o $@

clean:
	rm -f *.o
	rm -f *.gch

