#ifndef BBOXH
#define BBOXH

#include "glm/glm.hpp"
#include "ray.h"
#include "hitable.h"
#include <vector>

/// individual members of the bounding-volume-hierarchy
class bounding_box {
public:
	/// check whether ray hits bounding box
	bool hit(ray & r,float t_min,float t_max) const;
	vec3 min_bound();
	vec3 max_bound();
	float volume();
	bool in_box(vec3 min,vec3 max);
	//construct from list of hitables
	bounding_box(){}
	bounding_box(vec3 Min,vec3 Max,hitable** h,int n);
	bounding_box(vec3 Min,vec3 Max,std::vector<hitable*> &h,int n);

//private:
	std::vector<hitable*> inside;
	///determined at construction
	int numobjects;
	/// min bound/bottom left vector
	vec3 bound1;
	/// max bound/top right vector
	vec3 bound2;
};

#endif