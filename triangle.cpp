
#include triangle.h

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

