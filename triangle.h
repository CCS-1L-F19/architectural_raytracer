#pragma once

#include "glm/glm.hpp"
#include "hitable.h"
#include "material.h"
#include "ray.h"

using namespace glm;

class triangle : public hitable {

public:
	vec3 p1,p2,p3;
	vec3 normal,negnormal;
	bool overlap(vec3 axis,vec3 min,vec3 max);

public:
	triangle();
	triangle(vec3 p1,vec3 p2,vec3 p3,vec3 normal,material* matptr);
	triangle(vec3 p1,vec3 p2,vec3 p3,material* matptr);
	~triangle();
	vec3 min_bound();
	vec3 max_bound();
	bool hit(ray & r,float t_min,float t_max,hit_record & rec) const;
	bool in_box(vec3 min,vec3 max);
	
};