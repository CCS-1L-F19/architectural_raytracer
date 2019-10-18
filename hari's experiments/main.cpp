#include <iostream>
#include "ray.h"
#include <math.h>
#include "hitable.h"
#include "camera.h"
#include "sphere.h"
#include <cstdlib>
#include "hitable_list.h"

float ran(){
	return 0.999f*float(rand())/RAND_MAX;
};


vec3 random_in_sphere(){
	vec3 v;
	do{
		v = vec3(ran(),ran(),ran());
		v -= 0.5f;
		v *= 2;
	} while (length(v) >= 1);
	return v;
}

vec3 blend(ray &r,hitable_list* world,int bounces){
	bool hit;
	hit_record rec;
	rec.mat_ptr = NULL;
	hit = world->hit(r,0.0001,2.4e+30,rec);
	if(hit){
		ray scattered;
		vec3 attenuation;
		if(bounces < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
			return attenuation * blend(scattered,world,bounces + 1);
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
	srand(time(NULL));
	int width = 800;
	int height = 400;
	int rays_per_pixel = std::atoi(argv[1]);
	int size = 3;
	hitable* worl[size];
	worl[0] = new sphere(vec3(-0.5,0,-1),0.5f,new diffuse(vec3(0.8,0.2,0.2)));
	worl[1] = new sphere(vec3(0.5,0,-1),0.5f,new metal(vec3(0.8,0.8,0.8),0.1f));
	worl[size - 1] = new sphere(vec3(0,-100.5,-1),100.0f,new diffuse(vec3(0.8,0.8,0)));
	hitable_list world = hitable_list(worl,size);
	vec3 origin = vec3(std::atof(argv[2]),std::atof(argv[3]),std::atof(argv[4]));
	vec3 lookat =  vec3(0,0,-1);
	vec3 vertical =  vec3(0,2.0,0);
	vec3 horizontal =  vec3(4.0,0,0);
	vec3 color;
	camera cam = camera(origin,lookat,90,float(width)/float(height));
	float u,v;
	std::cout << "P3\n" << width << " "<< height << "\n255\n";
	for(int i = height-1;i>=0;i--){
		for(int j=0;j<width;j++){
			vec3 col = vec3(0,0,0);
			for(int s=0;s<rays_per_pixel;s++){
				u = float(j+ran())/float(width);
				v = float(i+ran())/float(height);
				ray r = cam.get_ray(u,v);
				col = col + blend(r,&world,1);
			}
			col /= rays_per_pixel;
			col.x = sqrt(col.x);
			col.y = sqrt(col.y);
			col.z = sqrt(col.z);
			col *= 255.99f;
			std::cout << int(col.x) <<" "<<int(col.y)<<" "<<int(col.z)<<"\n";
		}
	}

}


