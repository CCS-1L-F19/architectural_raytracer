#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include <math.h>
#include "glm/glm.hpp"

class sphere : public hitable {
	public:
	vec3 center;
	float radius;
	sphere(){}
	sphere(vec3 cen,float r){radius = r;center = cen;}
	
	virtual bool hit(ray & r,float t_min,float t_max,hit_record & rec) const {
		vec3 A = r.origin();
		vec3 B = r.dir();
		float a = dot(B,B);
		float b = 2* dot(B,A-center);
		float c = (dot(A-center,A-center) - pow(radius,2));
		
		float discriminant = sqrt(b*b - 4*a*c);
		if(discriminant > 0){
			float time = (-b - discriminant)/(2*a);
			if(time > t_min && time < t_max){
				rec.t = time;
				rec.p = r.point_at_t(time);
				rec.normal = normalize(rec.p - center);
				return true;
			}
			time = (-b + discriminant)/(2*a);
			if(time > t_min && time < t_max){
				rec.t = time;
				rec.p = r.point_at_t(time);
				rec.normal = normalize(rec.p - center);
				return true;
			}
		}
		return false;
	}
	
};

#endif
