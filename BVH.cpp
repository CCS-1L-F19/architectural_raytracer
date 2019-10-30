#include "BVH.h"
#include <vector>

void makeTree(Node* root){

	if(root->b.volume() <= 8.0f){
		root->left = NULL;
		root->right = NULL;
		return;
	}
	root->left = new Node;
	root->right = new Node;

	vec3 leftmin,rightmin,leftmax,rightmax;
	rightmax = root->b.bound2;
	leftmin = root->b.bound1;
	switch(root->axis){
		case 0:
			leftmax = vec3((root->b.bound2.x + root->b.bound1.x)/2.0,root->b.bound2.y,root->b.bound2.z);
			rightmin = vec3((root->b.bound2.x + root->b.bound1.x)/2.0,root->b.bound1.y,root->b.bound1.z);
			root->left->axis = root->axis + 1;
			root->right->axis = root->axis + 1;
			break;
		case 1:
			leftmax = vec3(root->b.bound2.x,(root->b.bound2.y + root->b.bound1.y)/2.0,root->b.bound2.z);
			rightmin = vec3(root->b.bound1.x,(root->b.bound2.y + root->b.bound1.y)/2.0,root->b.bound1.z);
			root->left->axis = root->axis + 1;
			root->right->axis = root->axis + 1;
			break;
		case 2:
			leftmax = vec3(root->b.bound2.x,root->b.bound2.y,(root->b.bound2.z + root->b.bound1.z)/2.0);
			rightmin = vec3(root->b.bound1.x,root->b.bound1.y,(root->b.bound2.z + root->b.bound1.z)/2.0);
			root->left->axis = 0;
			root->right->axis = 0;
			break;
	}

	std::vector<hitable*> leftobj;
	std::vector<hitable*> rightobj;
	for(int i =0;i<root->b.numobjects;i++){
		if((root->b.inside)[i]->in_box(leftmin,leftmax)){
			leftobj.push_back((root->b.inside)[i]);
		}
		if((root->b.inside)[i]->in_box(rightmin,rightmax)){
			rightobj.push_back((root->b.inside)[i]);
		}
	}

	root->left->b = bounding_box(leftmin,leftmax,leftobj,leftobj.size());
	root->right->b = bounding_box(rightmin,rightmax,rightobj,rightobj.size());

	makeTree(root->left);
	makeTree(root->right);

}

BVH::BVH(hitable** world,int n,vec3 b1,vec3 b2){
	numobjects = n;
	for(int i =0;i<n;i++){
		objects.push_back(world[i]);
	}

	root = new Node;
	root->b = bounding_box(b1,b2,objects,n);
	root->axis = 0;
	makeTree(root);
}

BVH::BVH(std::vector<hitable*> world,int n,vec3 b1,vec3 b2){
	numobjects = n;

	objects = world;

	root = new Node;
	root->b = bounding_box(b1,b2,objects,n);
	root->axis = 0;
	makeTree(root);
}

std::vector<hitable*> BVH::hit(ray &r,float t_min,float t_max){
	std::set<hitable*> o;
	if(root->b.hit(r,t_min,t_max)){
		recursiveHit(r,t_min,t_max,root,o);
	} else {
		o.insert(objects.at(objects.size() - 1));
	}
	std::vector<hitable*> v(o.begin(),o.end());
	return v;
}

void BVH::recursiveHit(ray &r,float t_min,float t_max,Node* roott,std::set<hitable*> &o){
	if(roott->left == NULL || roott->right == NULL){
		o.insert(root->b.inside.begin(),root->b.inside.end());
		return;
	}
	if(roott->left->b.hit(r,t_min,t_max)){
		recursiveHit(r,t_min,t_max,roott->left,o);
	}
	if(roott->right->b.hit(r,t_min,t_max)){
		recursiveHit(r,t_min,t_max,roott->right,o);
	}
}