#include <iostream>
#include "ray.cpp"
#include <math.h>
#include "hitable.cpp"
#include "camera.cpp"
#include "sphere.cpp"


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

vec3 blend(ray &r,hitable* world[],int size){
	bool hit;
	hit_record rec;
	for(int i =0;i<size;i++){
       		hit = world[i]->hit(r,0.01,MAXFLOAT,rec);
		if(hit){
			ray new_ray = ray(rec.p,rec.normal+random_in_sphere());
			return (0.5f * blend(new_ray,world,2));
		}
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
	int width = 800;
	int height = 400;
	int rays_per_pixel = std::atoi(argv[1]);
	int size = 3;
	hitable* world[size];
	world[0] = new sphere(vec3(0,0,-1),0.5f);
	world[2] = new sphere(vec3(0,-100.5,-1),100);
	world[1] = new sphere(vec3(1,0,-1),0.5f);
	vec3 origin = vec3(0,0,0);
	vec3 lower_left =  vec3(-2,-1,-1);
	vec3 vertical =  vec3(0,2.0,0);
	vec3 horizontal =  vec3(4.0,0,0);
	vec3 color;
	camera cam = camera(lower_left,origin,90,float(width)/float(height));
	float u,v;
	std::cout << "P3\n" << width << " "<< height << "\n255\n";
	for(int i = height-1;i>=0;i--){
		for(int j=0;j<width;j++){
			vec3 col = vec3(0,0,0);
			for(int s=0;s<rays_per_pixel;s++){
				u = float(j+ran())/float(width);
				v = float(i+ran())/float(height);
				ray r = cam.get_ray(u,v);
				col = col + blend(r,world,size);
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


