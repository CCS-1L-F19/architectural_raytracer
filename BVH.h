#ifndef BVHH
#define BVHH

#include "glm/glm.hpp"
#include "bounding_box.h"
#include "hitable.h"
#include <vector>
#include <set>

struct Node {
	Node* left;
	Node* right;
	int axis; //axis to split left and right along
	//0:x,1:y,2:z
	bounding_box b;
	Node(){}
};

class BVH{

public:
	BVH(hitable** world,int n,vec3 b1,vec3 b2);
	BVH(std::vector<hitable*> world,int n,vec3 b1,vec3 b2);
	std::set<hitable*> hit(ray &r,float t_min,float t_max);
	void hit(ray &r,float t_min,float t_max,std::set<hitable*>& o);
	void recursiveHit(ray &r,float t_min,float t_max,Node* roott,std::set<hitable*> &o); //used roott because root is local Node*

//private:
	Node* root;
	int numobjects;
	std::vector<hitable*> objects;
};


#endif