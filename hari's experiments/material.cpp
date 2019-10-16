#include "ray.h"
#include "material.h"
#include <iostream>

vec3 random_in_sphere();

bool diffuse::scatter(ray& r_in,hit_record& rec, vec3& attenuation,ray& scattered) const {
	scattered = ray(rec.p,rec.normal+random_in_sphere());
	attenuation = albedo;
	return true;
}

vec3 reflect(const vec3& v,const vec3& n){
	return (v- 2*dot(v,n)*n);
}

bool metal::scatter( ray& r_in, hit_record& rec, vec3& attenuation,ray& scattered) const {
	vec3 reflected = reflect(r_in.dir(),rec.normal);
	scattered = ray(rec.p,reflected);
	attenuation = albedo;
	return true;
}