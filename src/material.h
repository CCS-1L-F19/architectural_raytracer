#ifndef MATERIALH
#define MATERIALH


#include "glm/glm.hpp"
#include "ray.h"
#include "hitable.h"

/// ABSTRACT -- all materials will scatter() light in different ways
class material{
	public:
		virtual bool scatter( ray& r_in, hit_record& rec, vec3& attenuation,ray& scattered) const = 0;
};

/// lambertian material
class diffuse : public material{
	public:
		vec3 albedo;
		diffuse(vec3 a){albedo = a;}
		/// rays are randomly scattered to produce diffuse effect
		virtual bool scatter( ray& r_in, hit_record& rec, vec3& attenuation,ray& scattered) const;
};

/// reflective metal
class metal : public material{
	public:
		vec3 albedo;
		float fuzz;
		metal(vec3 a,float f){albedo = a;fuzz = f;}
		/// rays are perfectly reflected for shiny reflectiveness
		virtual bool scatter( ray& r_in, hit_record& rec, vec3& attenuation,ray& scattered) const;
};

/// clear material
class dielectric : public material {
    public:
    	float ref_idx;
        dielectric(float ri) : ref_idx(ri) {}
        /// rays are refracted and reflected
        virtual bool scatter(ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const;
};

#endif