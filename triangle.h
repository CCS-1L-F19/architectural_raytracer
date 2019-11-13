#pragma once

#include "glm/glm.hpp"
#include "hitable.h"
#include "material.h"
#include "ray.h"

using namespace glm;

class triangle : public hitable {

private:
	vec3 p1,p2,p3;
	vec3 normal;

public:
	triangle();
	~triangle();
	vec3 min_bound();
	vec3 max_bound();
	bool hit(ray & r,float t_min,float t_max,hit_record & rec) const;
	bool in_box(vec3 min,vec3 max);
	
};