#include <iostream>
#include <fstream>
#include "ray.h"
#include <math.h>
#include "hitable.h"
#include "camera.h"
#include "sphere.h"
#include <cstdlib>
#include "hitable_list.h"
#include <time.h>
#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include "BVH.h"
#include <vector>

static unsigned int g_seed;

inline void fast_srand( int seed ){
	g_seed = seed;
}

inline int fastrand() { 
  g_seed = (214013*g_seed+2531011); 
  return (g_seed>>16)&0x7FFF; 
}



float ran(){
	return 0.999f*float(rand())/RAND_MAX;
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

std::vector<hitable*> random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    int i = 0;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(
                        center, 0.2,
                        new diffuse(vec3(drand48()*drand48(),
                                            drand48()*drand48(),
                                            drand48()*drand48()))
                    );
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(
                        center, 0.2,
                        new metal(vec3(0.5*(1 + drand48()),
                                       0.5*(1 + drand48()),
                                       0.5*(1 + drand48())),
                                  0.5*drand48())
                    );
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new diffuse(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    list[i++] =  new sphere(vec3(0,-1000,0), 1000, new diffuse(vec3(0.5, 0.5, 0.5)));

    std::vector<hitable*> v(list,list+i);
    return v;
}

vec3 blend(ray &r,int bounces,hitable_list& world){
	bool hit;
	hit_record rec;
	rec.mat_ptr = NULL;
	hit = world.hit(r,0.0001,2.4e+30,rec);
	if(hit){
		ray scattered;
		vec3 attenuation;
		if(bounces < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
			return attenuation * blend(scattered,bounces + 1,world);
		} else {
			return vec3(0,0,0);
		}
	}

	//x range: -2 to 2
	//y range: -1 to 1
	vec3 white = vec3(1,1,1);
	vec3 blue =vec3(0.52,0.808,0.92);
	float t = 0.5f*(normalize(r.dir()).y + 1);
	return t*(blue - white) + white;
}

int main(int argc, char * argv[]){
	const clock_t begin_time = clock();

	fast_srand(0);
	srand(time(NULL));
	srand48(time(0));
	const int width = 800;
	const int height = 400;
	int rays_per_pixel = std::atoi(argv[1]);
	int size = 3;
	hitable* worl[size];
	/*
	worl[0] = new sphere(vec3(-1,1,1),0.4f,new diffuse(vec3(0.8,0.2,0.2)));
	worl[1] = new sphere(vec3(1,1,1),0.5f,new diffuse(vec3(0.5,0.5,0.5)));
	worl[size - 1] = new sphere(vec3(0,-100.5,-1),100.0f,new diffuse(vec3(0.8,0.8,0)));
	*/

	std::vector<hitable*> wor = random_scene();

	//BVH hierarchy = BVH(wor,wor.size(),vec3(-11,-0.5,-11),vec3(11,3.5,11));
	//std::cout << "Tree made" << std::endl;
	hitable_list world = hitable_list(wor);

	/*
	Node* n = hierarchy.root->left->left->right;
	std::cout << n->b.bound1.x << ",";
	std::cout << n->b.bound1.y << ",";
	std::cout << n->b.bound1.z << ":";
	std::cout << n->b.bound2.x << ",";
	std::cout << n->b.bound2.y << ",";
	std::cout << n->b.bound2.z << ":";
	std::cout << n->b.inside.size() << std::endl;
	*/

	vec3 origin = vec3(std::atoi(argv[2]),std::atoi(argv[3]),std::atoi(argv[4]));
	vec3 lookat =  vec3(0,1,0);
	vec3 color;
	vec3 pixels[width*height];
	camera cam = camera(origin,lookat,65,float(width)/float(height));
	float u,v;
	float cent = 0;
	//std::cout << "P3\n" << width << " "<< height << "\n255\n";
	for(int i = height-1;i>=0;i--){
		for(int j=0;j<width;j++){
			vec3 col = vec3(0,0,0);
			for(int s=0;s<rays_per_pixel;s++){
				u = float(j+ran())/float(width);
				v = float(i+ran())/float(height);
				ray r = cam.get_ray(u,v);
//std::cout << "Hello" <<std::endl;
				col = col + blend(r,1,world);
//std::cout << "bye";
			}
			col /= rays_per_pixel;
			col.x = sqrt(col.x);
			col.y = sqrt(col.y);
			col.z = sqrt(col.z);
			col *= 255.99f;
			//std::cout << int(col.x) <<" "<<int(col.y)<<" "<<int(col.z)<<"\n";
			pixels[(height-1 -i)*width + j] = vec3(int(col.x),int(col.y),int(col.z));
		}if(i%(height/20) == 0){cent += 0.05; std::cout << cent << " done" << std::endl;}
	}
	std::ofstream file;
	file.open("hell.ppm");
	file << "P3\n" << width << " "<< height << "\n255\n";
	for(int i =0;i<width*height;i++){
		file << pixels[i].x <<" "<< pixels[i].y <<" "<< pixels[i].z <<"\n";
	}
	std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
}


