#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include <math.h>
#include "glm/glm.hpp"
#include "material.h"


class sphere : public hitable {
	public:
	vec3 center;
	float radius;
	material* matptr;

	sphere(){};
	sphere(vec3 cen,float r,material* m);
	
	bool hit(ray & r,float t_min,float t_max,hit_record & rec) const;
			
};

#endif
