#ifndef CAMERAH
#define CAMERAH
#include "ray.h"
#include <math.h>
class camera {
	public:
	vec3 lower_left,width,height,origin;
	float vfov,aspect;
	float half_height,half_width;
	float theta;
	camera(vec3 lookfrom,vec3 lookat,float fovvert,float aspect_ratio);
	ray get_ray(float s,float d);
};

#endif
