#ifndef MATERIALH
#define MATERIALH


#include "glm/glm.hpp"
#include "ray.h"
#include "hitable.h"

class material{
	public:
		virtual void scatter(ray& r_in,hit_record& rec, vec3& attenuation,ray& scattered) const = 0;
};

class diffuse : public material{
	public:
		vec3 albedo;
		diffuse(vec3& a){albedo = a;}
		virtual void scatter(ray& r_in,hit_record& rec, vec3& attenuation,ray& scattered) const;
};

class metal : public material{
	public:
		vec3 albedo;
		metal(vec3& a){albedo = a;}
		vec3 reflect(const vec3& v,const vec3& n) const;
		virtual void scatter(ray& r_in,hit_record& rec, vec3& attenuation,ray& scattered) const;
};

#endif