#include "camera.h"
#include "ray.h"
camera::camera(vec3 lookfrom,vec3 lookat,float fovvert,float aspect_ratio){
		vec3 u,v,w,vup;
		vup = vec3(0,1,0);
		origin = lookfrom;
		vfov = fovvert;
		aspect = aspect_ratio;
		w = normalize(lookfrom - lookat);
		u = normalize(cross(vup,w));
		v = -1.0f*normalize(cross(u,w));
		theta = vfov * M_PI / 180;
		half_height = tan(theta/2);
		half_width = half_height * aspect;
		height = v*half_height*2.0f;
		width = u*half_width*2.0f;
		lower_left = origin - half_height*v - half_width*u -w;
}
ray camera::get_ray(float s,float d){return ray(origin,lower_left + s*width + d*height - origin);}

