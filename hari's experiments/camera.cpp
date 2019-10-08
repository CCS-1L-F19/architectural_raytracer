#ifndef CAMERAH
#define CAMERAH
#include <math.h>
#include "ray.cpp"

class camera {
	public:
	vec3 lower_left,horizontal,vertical,origin;
	float vfov,aspect;
	float theta;

	camera(vec3 ll,vec3 o,float fovvert,float aspect_ratio){
		lower_left = ll;
		origin = o;
		vfov = fovvert;
		aspect = aspect_ratio;
		theta = vfov * M_PI / 180;
		vertical = vec3(0,tan(theta/2)*2,0);
		horizontal = vec3(aspect * vertical.y,0,0);
	}
	ray get_ray(float u,float v){return ray(origin,lower_left + u*horizontal + v*vertical);}
};

#endif
