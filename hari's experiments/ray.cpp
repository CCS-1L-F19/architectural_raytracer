
#ifndef RAYH
#define RAYH

#include "glm/glm.hpp"
using namespace glm;

class ray{
	public:
	
	vec3 a;
	vec3 b;
	
	ray(){}
	ray(const vec3 & A,const vec3 & B){a = A;b = B;}

	vec3 origin(){return a;}
	vec3 dir(){return b;}
	vec3 point_at_t(float t){return a + b*t;}
};

#endif
