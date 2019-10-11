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

vec3 blend(ray &r,hitable_list* world){
	bool hit;
	hit_record rec;
	hit = world->hit(r,0.0001,MAXFLOAT,rec);
	if(hit){
		ray new_ray = ray(rec.p,rec.normal + random_in_sphere());
		return 0.5f * blend(new_ray,world);
	}

	//x range: -2 to 2
	//y range: -1 to 1
	vec3 white = vec3(1,1,1);
	vec3 blue =vec3(0.52,0.808,0.92);
	float t = 0.5f*(normalize(r.dir()).y + 1);
	return t*(blue - white) + white;
};

int main(int argc, char * argv[]){
	srand(time(NULL));
	int width = 1000;
	int height = 500;
	int rays_per_pixel = std::atoi(argv[1]);
	int size = 3;
	hitable* worl[size];
	worl[0] = new sphere(vec3(0,0,-1),0.5f);
	worl[1] = new sphere(vec3(1,0,-1),0.5f);
	worl[size - 1] = new sphere(vec3(0,-100.5,-1),100.0f);
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
				col = col + blend(r,&world);
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


