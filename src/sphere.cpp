#include "sphere.h"
#include "material.h"
#include <math.h>

/// not used
vec3 sphere::min_bound(){
	return (center - 1.0f);
}

/// not used
vec3 sphere::max_bound(){
	return (center + 1.0f);
}


/// mathematically determine sphere-line intersection, and modify hit_record parameter
bool sphere::hit(ray & r,float t_min,float t_max,hit_record & rec) const {
		vec3 A = r.origin();
		vec3 B = r.dir();
		float a = dot(B,B);
		float b = 2* dot(B,A-center);
		float c = (dot(A-center,A-center) - pow(radius,2));
		
		float discriminant = b*b - 4*a*c;
		if(discriminant > 0){
			discriminant = sqrt(discriminant);
			float time = (-b - discriminant)/(2*a);
			if(time > t_min && time < t_max){
				rec.t = time;
				rec.p = r.point_at_t(time);
				rec.normal = normalize(rec.p - center);
				rec.mat_ptr = matptr;
				return true;
			}
			time = (-b + discriminant)/(2*a);
			if(time > t_min && time < t_max){
				rec.t = time;
				rec.p = r.point_at_t(time);
				rec.normal = normalize(rec.p - center);
				rec.mat_ptr = matptr;
				return true;
			}
		}
		return false;	
}

/// test sphere-box intersection to be used in bounding volume hierarchy
bool sphere::in_box(vec3 min,vec3 max){

	if(center.x < max.x && center.x > min.x && center.y < max.y && center.y > min.y && center.z < max.z && center.z > min.z){
		return true;
	}

	float dist2 = pow(radius,2);

	if(center.x < min.x){
		dist2 -= pow(min.x - center.x,2);
	} else if(center.x > max.x){
		dist2 -= pow(max.x - center.x,2);
	}

	if(center.y < min.y){
		dist2 -= pow(min.y - center.y,2);
	} else if(center.y > max.y){
		dist2 -= pow(max.y - center.y,2);
	}

	if(center.y < min.z){
		dist2 -= pow(min.z - center.z,2);
	} else if(center.z > max.z){
		dist2 -= pow(max.z - center.z,2);
	}
	return (dist2 > 0);
}


sphere::sphere(vec3 cen,float r,material* m){radius = r;center = cen; matptr = m;}
