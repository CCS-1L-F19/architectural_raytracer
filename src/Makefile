CXX = g++

CXXFLAGS = -Wall -Wextra -g

main: main.o camera.o sphere.o triangle.o material.o bounding_box.o BVH.o
	g++ -g $^ -o $@
	
main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp 
material.o: material.cpp
	${CXX} ${CXXFLAGS} -c material.cpp
camera.o: camera.cpp
	${CXX} ${CXXFLAGS} -c camera.cpp
sphere.o: sphere.cpp
	${CXX} ${CXXFLAGS} -c sphere.cpp
triangle.o: triangle.cpp
	${CXX} ${CXXFLAGS} -c triangle.cpp
bounding_box.o: bounding_box.cpp
	${CXX} ${CXXFLAGS} -c bounding_box.cpp
BVH.o: BVH.cpp
	${CXX} ${CXXFLAGS} -c BVH.cpp


clean:
	rm -f *.o
	rm -f *.gch