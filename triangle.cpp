
#include "triangle.h"
#include <vector>

triangle::triangle(){
	p1 = vec3(0,0,0);
	p2 = vec3(0,0,0);
	p3 = vec3(0,0,0);
	normal = vec3(0,0,0);
	this->negnormal = vec3(0,0,0);
	matptr = NULL;
}

triangle::triangle(vec3 p1,vec3 p2,vec3 p3,vec3 normal,material* matptr){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->normal = normalize(normal);
	this->negnormal = -1.0f * this->normal;
	this->matptr = matptr;
}

triangle::triangle(vec3 p1,vec3 p2,vec3 p3,material* matptr){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->normal = normalize(cross(p1-p2,p3-p2));
	this->negnormal = -1.0f * this->normal;
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

bool triangle::overlap(vec3 axis,vec3 min,vec3 max){ //axis 

	float projmin = dot(min,axis);

	float projmax = dot(max,axis);

	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				vec3 corner;
				if(i){corner.x = min.x ;}
				else{corner.x = max.x ;}

				if(j){corner.y = min.y ;}
				else{corner.y = max.y ;}

				if(k){corner.z = min.z ;}
				else{corner.z = max.z ;}

				if(dot(corner,axis) > projmax)projmax = dot(corner,axis);
				if(dot(corner,axis) < projmin)projmin = dot(corner,axis);
			}
		}
	}

	float proj1 = dot(p1,axis);
	if(proj1 >= projmin && proj1 <= projmax)return true;

	float proj2 = dot(p2,axis);
	if(proj2 >= projmin && proj2 <= projmax)return true;

	float proj3 = dot(p3,axis);
	if(proj3 >= projmin && proj3 <= projmax)return true;

	return false;
}

bool triangle::in_box(vec3 min,vec3 max){
	

	//checking surface normals

	if(!overlap(normal,min,max))return false;
	if(!overlap(vec3(1,0,0),min,max))return false;
	if(!overlap(vec3(0,1,0),min,max))return false;
	if(!overlap(vec3(0,0,1),min,max))return false;

	if(!overlap(cross(p2-p1,vec3(1,0,0)),min,max))return false;
	if(!overlap(cross(p2-p1,vec3(0,1,0)),min,max))return false;
	if(!overlap(cross(p2-p1,vec3(0,0,1)),min,max))return false;


	if(!overlap(cross(p3-p2,vec3(1,0,0)),min,max))return false;
	if(!overlap(cross(p3-p2,vec3(0,1,0)),min,max))return false;
	if(!overlap(cross(p3-p2,vec3(0,0,1)),min,max))return false;

	if(!overlap(cross(p1-p3,vec3(1,0,0)),min,max))return false;
	if(!overlap(cross(p1-p3,vec3(0,1,0)),min,max))return false;
	if(!overlap(cross(p1-p3,vec3(0,0,1)),min,max))return false;

	return true;
}

bool sameSign(double x, double y){
	return ((x<0)==(y<0));
}


/*
bool triangle::hit(ray & r,float t_min,float t_max,hit_record & rec) const {
	float D = dot(normal,p1);
	float time = ((dot(normal,r.origin()) + D)/(dot(normal,r.dir())));
	
	if(!(time < 0)){
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
	} }
	
	D = dot(negnormal,p1);
	time = -((dot(negnormal,r.origin()) + D)/(dot(negnormal,r.dir())));
	if(time < 0){return false;}
	vec3 point = r.point_at_t(time);
	float side1 = dot(negnormal,cross(p2-p1,point-p1));
	float side2 = dot(negnormal,cross(p3-p2,point-p2));
	float side3 = dot(negnormal,cross(p1-p3,point-p3));
	if(sameSign(side1,side2) && sameSign(side2,side3)){
		rec.t = time;
		rec.p = point;
		rec.mat_ptr = matptr;
		rec.normal = negnormal;
		return true;
	}

	return false;
}*/


bool triangle::hit(ray & r,float t_min,float t_max,hit_record & rec) const {
    const float EPSILON = 0.000001;
    vec3 edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = p2 - p1;
    edge2 = p3 - p1;
    h = -1.0f*cross(r.dir(),edge2);
    a = dot(edge1,h);
    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    f = 1.0/a;
    s = r.origin() - p1;
    u = f * dot(s,h);
    if (u < 0.0 || u > 1.0)
        return false;
    q = -1.0f*cross(s,edge1);
    v = f * dot(r.dir(),q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * dot(edge2,q);
    if (t > EPSILON && t < 1/EPSILON) // ray intersection
    {
        vec3 outIntersectionPoint = r.origin() + r.dir() * t;
        rec.t = t;
        rec.p = outIntersectionPoint;
        rec.mat_ptr = matptr;
        if(dot(normal,r.dir()) > 0){
        	rec.normal = negnormal;
        } else {
        	rec.normal = normal;
        }
        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;
}