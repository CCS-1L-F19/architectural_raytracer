
#include "triangle.h"

triangle::triangle(vec3 p1,vec3 p2,vec3 p3,vec3 normal,material* matptr){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->normal = normal;
	this->matptr = matptr;
}

vec3 triangle::min_bound(){
	double x = (p1.x<p2.x) ? p1.x : p2.x;
	x = (x<p3.x) ? x : p3.x;
	double y = (p1.y<p2.y) ? p1.y : p2.y;
	y = (y<p3.y) ? y : p3.y;
	double z = (p1.z<p2.z) ? p1.z : p2.z;
	z = (z<p3.z) ? z : p3.z;
	return vec3(x,y,z);
}

vec3 triangle::max_bound(){
	double x = (p1.x>p2.x) ? p1.x : p2.x;
	x = (x>p3.x) ? x : p3.x;
	double y = (p1.y>p2.y) ? p1.y : p2.y;
	y = (y>p3.y) ? y : p3.y;
	double z = (p1.z<p2.z) ? p1.z : p2.z;
	z = (z<p3.z) ? z : p3.z;
	return vec3(x,y,z);
}

bool triangle::in_box(vec3 min,vec3 max){
	if(p1.x > min.x && p1.y > min.y && p1.z > min.z && p1.x < max.x && p1.y < max.y && p1.z < max.z){
		return true;
	}
	if(p2.x > min.x && p2.y > min.y && p2.z > min.z && p2.x < max.x && p2.y < max.y && p2.z < max.z){
		return true;
	}
	if(p3.x > min.x && p3.y > min.y && p3.z > min.z && p3.x < max.x && p3.y < max.y && p3.z < max.z){
		return true;
	}
	return false;
}

bool sameSign(double x, double y){
	return ((x<0)==(y<0));
}

bool triangle::hit(ray & r,float t_min,float t_max,hit_record & rec) const {
	float D = dot(normal,p1);
	float time = -1 * (dot(normal,r.origin()) + D/(dot(normal,r.dir())));
	if(time < 0){return false;}
	vec3 point = r.point_at_t(time);
	float side1 = dot(normal,cross(p2-p1,point-p1));
	float side2 = dot(normal,cross(p3-p2,point-p2));
	float side3 = dot(normal,cross(p1-p3,point-p3));
	if(sameSign(side1,side2) && sameSign(side2,side3)){
		rec.t = time;
		rec.p = point;
		rec.mat_ptr = matptr;
		rec.normal = normal;
		return true;
	} return false;
}