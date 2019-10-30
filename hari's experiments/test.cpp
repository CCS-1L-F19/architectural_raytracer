
#include "glm/glm.hpp"
#include <iostream>
#include <math.h>
#include "hitable.h"
#include "sphere.h"
#include "sphere.cpp"
#include "material.h"
#include "material.cpp"
#include "glm/gtx/norm.hpp"
#include "bounding_box.h"
#include "bounding_box.cpp"
#include "BVH.h"
#include "BVH.cpp"
#include <vector>
#include <set>

using namespace glm;
using namespace std;

float ran(){
	return 0.999f*float(rand())/32767;
};

vec3 random_in_sphere(){
	vec3 v;
	do{
		v = vec3(ran(),ran(),ran());
		v -= 0.5f;
		v *= 2;
	} while (length2(v) >= 1);
	return v;
}


int main(){
	srand(time(NULL));
	srand48(time(0));


	std::vector<hitable*> v;
	hitable* h[20];
	for(int i =0;i<20;i++){
		h[i] = new sphere(vec3(-0.5,0,-1),0.5f,new diffuse(vec3(0.8,0.2,0.2)));
	}
	v.assign(h,h+20);
	bounding_box b1 = bounding_box(vec3(8,8,8),vec3(10,10,10),v,20);
	std::cout << b1.inside[0]->min_bound().x << endl;

	/*
	BVH vh = BVH(h,20,vec3(-10,-10,-10),vec3(5,5,5));
	cout << vh.numobjects << endl;
	cout << vh.root->b.numobjects<<endl;
	cout << vh.root->right->right->right->left->left->left->right->right->right->b.numobjects<<endl;
	*/
	int arr[10];
	std::set<int*> a;
	for(int i =0;i<10;i++){
		arr[i] = i;
		a.insert(&arr[i]);
	}
	std::vector<int*> b(a.begin(),a.end());

	set<int*>::iterator ai = a.begin();
	for(int i = 0;i<b.size();i++){
		cout << b[i] << " ";
	}
}

