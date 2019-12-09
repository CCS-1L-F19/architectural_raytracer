#include "BVH.h"
#include <vector>
#include <iostream>
using namespace std;


void makeTree(Node* root){

	//std::cout << root->b.volume() << " space in this box" << std::endl;
	//std::cout << root->b.inside.size() << " triangles in this box" << std::endl;

	if(root->b.volume() <= 10.0f || root->b.inside.size() <= 2){
		root->left = NULL;
		root->right = NULL;
		//std::cout << root->b.inside.size() << " triangles in this box" << std::endl;
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
	//cout << leftobj.size() << "," << rightobj.size() << endl;
	root->left->b = bounding_box(leftmin,leftmax,leftobj,leftobj.size());
	root->right->b = bounding_box(rightmin,rightmax,rightobj,rightobj.size());
	//std::cout << "_________________" << std::endl;
	

	//makeTree(root->left);
	//makeTree(root->right);
	
	
	if(leftobj.size() > 1){makeTree(root->left);}
	else{delete root->left; root->left = NULL;}
	if(rightobj.size() > 1){makeTree(root->right);}
	else{delete root->right;root->right = NULL;}

	return;

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

std::set<hitable*> BVH::hit(ray &r,float t_min,float t_max){
	std::set<hitable*> o;
	if(root->b.hit(r,t_min,t_max)){
		recursiveHit(r,t_min,t_max,root,o);
	}
	o.insert(objects.at(objects.size() - 1));
	//if(o.size() > 1)cout << o.size() << endl;
	return o;
}

void BVH::hit(ray &r,float t_min,float t_max,std::set<hitable*>& o){
	if(root->b.hit(r,t_min,t_max)){
		recursiveHit(r,t_min,t_max,root,o);
	}
	return;
}

void BVH::recursiveHit(ray &r,float t_min,float t_max,Node* roott,std::set<hitable*> &o){
	if(roott->left == NULL && roott->right == NULL){
		o.insert(roott->b.inside.begin(),roott->b.inside.end());
		return;
	}
	if(roott->left && roott->left->b.hit(r,t_min,t_max)){
		recursiveHit(r,t_min,t_max,roott->left,o);
	}
	if(roott->right && roott->right->b.hit(r,t_min,t_max)){
		recursiveHit(r,t_min,t_max,roott->right,o);
	}
}