
#include "glm/glm.hpp"
#include <iostream>
#include "hitable.cpp"
#include "sphere.cpp"
#include <math.h>
using namespace glm;
int main(){
	srand(time(NULL));
	vec3 v = vec3(3,2,4);
	v*= 2;
	v +=1;
	std::cout << v.x<<" "<<v.y<<std::endl;
	std::cout << M_PI<<std::endl;
}

