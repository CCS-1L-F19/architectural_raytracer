#ifndef MATERIALH
#define MATERIALH


#include "glm/glm.hpp"
#include "ray.h"
#include "hitable.h"

class material{
	public:
		virtual bool scatter( ray& r_in, hit_record& rec, vec3& attenuation,ray& scattered) const = 0;
};

class diffuse : public material{
	public:
		vec3 albedo;
		diffuse(vec3 a){albedo = a;}
		virtual bool scatter( ray& r_in, hit_record& rec, vec3& attenuation,ray& scattered) const;
};

class metal : public material{
	public:
		vec3 albedo;
		float fuzz;
		metal(vec3 a,float f){albedo = a;fuzz = f;}
		virtual bool scatter( ray& r_in, hit_record& rec, vec3& attenuation,ray& scattered) const;
};

#endif