#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include <math.h>
#include "glm/glm.hpp"
#include "material.h"

class sphere : public hitable {

private:
	vec3 center;
	float radius;

public:
	sphere(){};
	sphere(vec3 cen,float r,material* m);
	
	vec3 min_bound();
	vec3 max_bound();
	/// ray-sphere intersection is mathematically determined
	bool hit(ray & r,float t_min,float t_max,hit_record & rec) const;
	/// sphere-box intersection test
	bool in_box(vec3 min,vec3 max);
			
};

#endif
