#include "bounding_box.h"
#include <iostream>

vec3 bounding_box::min_bound(){
	return bound1;
}

vec3 bounding_box::max_bound(){
	return bound2;
}

float bounding_box::volume(){
	return ((bound2.x - bound1.x)*(bound2.y - bound1.y)*(bound2.z - bound1.z));
}

bounding_box::bounding_box(vec3 Min,vec3 Max,hitable** h,int n){
	bound1 = Min;
	bound2 = Max;
	inside.assign(h,h+n);
	numobjects = n;
}

bounding_box::bounding_box(vec3 Min,vec3 Max,std::vector<hitable*> &h,int n){
	bound1 = Min;
	bound2 = Max;
	inside = h;
	numobjects = n;
}

bool bounding_box::hit(ray & r,float t_min,float t_max) const {

	//std::cout << "Origin: " << r.origin().x << ","<<r.origin().y <<","<<r.origin().z << std::endl;
	//std::cout << "Dir: " << r.dir().x << ","<<r.dir().y <<","<<r.dir().z << std::endl;

	//std::cout << "B1: " << bound1.x << ","<<bound1.y <<","<<bound1.z << std::endl;
	//std::cout << "B2: " << bound2.x << ","<<bound2.y <<","<<bound2.z << std::endl << std::endl;

	if(r.dir().x != 0){
		float t1x = (bound1.x - r.origin().x) / r.dir().x;
		float t2x = (bound2.x - r.origin().x) / r.dir().x;
		if(t1x > t_min && t1x < t_max && r.point_at_t(t1x).y > bound1.y && r.point_at_t(t1x).y < bound2.y && r.point_at_t(t1x).z > bound1.z && r.point_at_t(t1x).z < bound2.z){
			return true;
		}
		if(t2x > t_min && t2x < t_max && r.point_at_t(t2x).y > bound1.y && r.point_at_t(t2x).y < bound2.y && r.point_at_t(t2x).z > bound1.z && r.point_at_t(t2x).z < bound2.z){
			return true;
		}
	}
	if(r.dir().y != 0){
		float t1y = (bound1.y - r.origin().y) / r.dir().y;
		float t2y = (bound2.y - r.origin().y) / r.dir().y;
		if(t1y > t_min && t1y < t_max && r.point_at_t(t1y).x > bound1.x && r.point_at_t(t1y).x < bound2.x && r.point_at_t(t1y).z > bound1.z && r.point_at_t(t1y).z < bound2.z){
			return true;
		}
		if(t2y > t_min && t2y < t_max && r.point_at_t(t2y).x > bound1.x && r.point_at_t(t2y).x < bound2.x && r.point_at_t(t2y).z > bound1.z && r.point_at_t(t2y).z < bound2.z){
			return true;
		}
	}
	if(r.dir().z != 0){
		float t1z = (bound1.z - r.origin().z) / r.dir().z;
		float t2z = (bound2.z - r.origin().z) / r.dir().z;
		if(t1z > t_min && t1z < t_max && r.point_at_t(t1z).y > bound1.y && r.point_at_t(t1z).y < bound2.y && r.point_at_t(t1z).x > bound1.x && r.point_at_t(t1z).x < bound2.x){
			return true;
		}
		if(t2z > t_min && t2z < t_max && r.point_at_t(t2z).y > bound1.y && r.point_at_t(t2z).y < bound2.y && r.point_at_t(t2z).x > bound1.x && r.point_at_t(t2z).x < bound2.x){
			return true;
		}
	}
	return false;
}

bool bounding_box::in_box(vec3 min,vec3 max){
	// TODO? 
	return false;
}