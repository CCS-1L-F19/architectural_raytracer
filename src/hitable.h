#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

/// parent of specific material classes
class material;

/// modified to keep track of the 'hits' that a ray makes
struct hit_record{
	float t;
	vec3 p;
	vec3 normal;
	material* mat_ptr;
};

/// a virtual class from which all objects inherit 
class hitable{
	public:
		virtual bool hit(ray & r,float t_min,float t_max,hit_record & rec) const = 0;
		virtual vec3 min_bound() = 0;
		virtual vec3 max_bound() = 0;
		virtual bool in_box(vec3 min,vec3 max) = 0;

	protected:
		material* matptr;
};

#endif
