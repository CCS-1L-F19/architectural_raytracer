#pragma once

#include "glm/glm.hpp"
#include "hitable.h"
#include "material.h"
#include "ray.h"

using namespace glm;

/// Triangle class used in drawing any stl file
class triangle : public hitable {

public:
	vec3 p1,p2,p3;
	/// two normals used in order to ensure triangle will be visible in any orientation
	vec3 normal,negnormal;
	bool overlap(vec3 axis,vec3 min,vec3 max);

public:
	triangle();
	triangle(vec3 p1,vec3 p2,vec3 p3,vec3 normal,material* matptr);
	triangle(vec3 p1,vec3 p2,vec3 p3,material* matptr);
	~triangle();
	vec3 min_bound();
	vec3 max_bound();
	/// determine whether ray hits triangle using inside-outside test
	bool hit(ray & r,float t_min,float t_max,hit_record & rec) const;
	/// determine whether triangle is inside a bounding-box using Seperating Axis Theorem
	bool in_box(vec3 min,vec3 max);
	
};