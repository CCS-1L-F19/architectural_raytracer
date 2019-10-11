
#include "glm/glm.hpp"
#include <iostream>
#include "hitable.h"
#include "sphere.h"
#include "sphere.cpp"
#include <math.h>
using namespace glm;
int main(){
	srand(time(NULL));
	vec3 v = vec3(3,2,4);
	sphere s = sphere(v,0.5f);
	std::cout << &s <<std::endl;
	std::cout << M_PI<<std::endl;
}

