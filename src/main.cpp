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
#include "triangle.h"
#include <vector>
#include <set>
#include <string>


using namespace std;
using namespace glm;

using std::endl;
using std::cerr;
using std::string;

static unsigned int g_seed;

inline void fast_srand(int seed)
{
	g_seed = seed;
}

inline int fastrand()
{
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16) & 0x7FFF;
}

float ran()
{
	return 0.999f * float(rand()) / RAND_MAX;
};

vec3 random_in_sphere()
{
	vec3 v;
	do
	{
		v = vec3(ran(), ran(), ran());
		v -= 0.5f;
		v *= 2;
	} while (length2(v) >= 1);
	return v;
}

void consv3(vec3& v,char* facet) {

    char f1[4] = {facet[0],
        facet[1],facet[2],facet[3]};

    char f2[4] = {facet[4],
        facet[5],facet[6],facet[7]};

    char f3[4] = {facet[8],
        facet[9],facet[10],facet[11]};

    v.x = *((float*) f1 );
    v.y = *((float*) f2 );
    v.z = *((float*) f3 );

	return;

}

void read_stl(string fname, vector <hitable*>&v, vec3 &min, vec3 &max){

    //!!
    //don't forget ios::binary
    //!!
    ifstream myFile (
        fname.c_str(), ios::in | ios::binary);

    char header_info[80] = "";
    char nTri[4];

    //read 80 byte header
    if (myFile) {
        myFile.read (header_info, 80);
        cout << fname.substr(13,fname.size()) + string(" header: ") << header_info << endl;
    }
    else{
        cerr << "Error while reading .stl file: file does not exist" << endl;
        exit(1);
    }

    //read 4-byte ulong
    if (myFile) {
        myFile.read (nTri, 4);
    }
    else{
        cerr << "Error while reading .stl file: file does not exist" << endl;
        exit(1);
    }

    //now read in all the triangles
    for(int i = 0; i < 350000; i++){

    	float scalestl = 1.0f;

        char facet[50];

        if (myFile) {

        //read one 50-byte triangle
            myFile.read (facet, 50);

        //populate each point of the triangle
        //using v3::v3(char* bin);
            //facet + 12 skips the triangle's unit normal
            float tmp;
            vec3 p1,p2,p3,normal;
            consv3(normal,facet);
            tmp = normal.y;
            normal.y = scalestl*normal.z;
            normal.z = scalestl*-1.0f * tmp;
            consv3(p1,facet+12);
            if(p1.x < min.x)min.x = p1.x;
            if(p1.x > max.x)max.x = p1.x;
            tmp = p1.y;
            p1.y = scalestl*p1.z;
            if(p1.y < min.y)min.y = p1.y;
            if(p1.y > max.y)max.y = p1.y;
            p1.z = scalestl*-1.0f * tmp;
            if(p1.z < min.z)min.z = p1.z;
            if(p1.z > max.z)max.z = p1.z;
            consv3(p2,facet+24);
            if(p2.x < min.x)min.x = p2.x;
            if(p2.x > max.x)max.x = p2.x;
            tmp = p2.y;
            p2.y = scalestl*p2.z;
            if(p2.y < min.y)min.y = p2.y;
            if(p2.y > max.y)max.y = p2.y;
            p2.z = scalestl*-1.0f * tmp;
            if(p2.z < min.z)min.z = p2.z;
            if(p2.z > max.z)max.z = p2.z;
            consv3(p3,facet+36);
            if(p3.x < min.x)min.x = p3.x;
            if(p3.x > max.x)max.x = p3.x;
            tmp = p3.y;
            p3.y = scalestl*p3.z;
            if(p3.y < min.y)min.y = p3.y;
            if(p3.y > max.y)max.y = p3.y;
            p3.z = scalestl*-1.0f * tmp;
            if(p3.z < min.z)min.z = p3.z;
            if(p3.z > max.z)max.z = p3.z;

            //cout << "p1: " << p1.x << "," << p1.y << "," << p1.z << endl;
            //add a new triangle to the array
            v.push_back(new triangle(p1,p2,p3,new metal(vec3(0.8,0.1,0.1),0.1f)));

            //add sphere
            //vec3 avg = (p1+p2+p3)/3.0f;
            //v.push_back(new sphere(avg,0.5f,new metal(vec3(0.9,0.1,0.1),0.1f)));
        }
    }

    return;

}

std::vector<hitable *> random_scene()
{
	int n = 500;
	hitable **list = new hitable *[n];
	int i = 0;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = drand48();
			vec3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
			//vec3 center(a,0.2,b);
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (choose_mat < 0.8)
				{ // diffuse
					list[i++] = new sphere(
						center, 0.2,
						new diffuse(vec3(drand48() * drand48(),
										 drand48() * drand48(),
										 drand48() * drand48())));
				}
				else if (choose_mat < 0.95)
				{ // metal
					list[i++] = new sphere(
						center, 0.2,
						new metal(vec3(0.5 * (1 + drand48()),
									   0.5 * (1 + drand48()),
									   0.5 * (1 + drand48())),
								  0.5 * drand48()));
				}
				else
				{ // glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), -1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new diffuse(vec3(1, 1, 0)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.4, 0.4, 0.8), 0.0));
	list[i++] = new triangle(vec3(-5,0,5),vec3(5,0,5),vec3(0,8,5),new metal(vec3(0.3,0.9,0.3),0.1f));
	list[i++] = new sphere(vec3(0, -1000, 0), 1000, new diffuse(vec3(0.5, 0.5, 0.5)));

	std::vector<hitable *> v(list, list + i);
	return v;
}

int boundedRays = 0;

vec3 blend(ray &r, int bounces, BVH &world)
{
	bool hit;
	hit_record rec;
	rec.mat_ptr = NULL;

	hitable_list obj = hitable_list(world.hit(r, 0, 2.4e+30));
	hit = obj.hit(r, 0.0001, 2.4e+30, rec);

	if (bounces != 1)
	{
		boundedRays++;
	}

	//hit = world.hit(r,0,2.4e+30,rec);

	if (hit)
	{
		ray scattered;
		vec3 attenuation;
		if (bounces < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * blend(scattered, bounces + 1, world);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}

	//x range: -2 to 2
	//y range: -1 to 1
	vec3 white = vec3(1, 1, 1);
	vec3 blue = vec3(0.52, 0.808, 0.92);
	float t = 0.5f * (normalize(r.dir()).y + 1);
	return t * (blue - white) + white;
}

void usage(char *argv[])
{
	cerr << "Usage: " << argv[0] << " filename.stl r x y z x2 y2 z2" << endl
		 << "    where r is rays per pixel" << endl
		 << "    x y z are coordinates of camera" << endl
		 << "    x2 y2 z2 are coordinates to look at" << endl;
}

int safe_int(const char * const varName, char *arg, char *argv[]) {
	try {
		return std::stoi(string(arg));
	}
	catch(std::exception const & e)
	{
		cerr << "Error parsing " << varName << " : " << e.what() << endl;
		usage(argv);
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 9)
	{
		usage(argv);
		exit(1);
	}

	const clock_t begin_time = clock();

	fast_srand(0);
	srand(time(NULL));
	srand48(time(0));

	string filename = string("../STL_files/") + string(argv[1]);
	int rays_per_pixel = safe_int("r", argv[2], argv);
	int x = safe_int("x", argv[3], argv);
	int y = safe_int("y", argv[4], argv);
	int z = safe_int("z", argv[5], argv);

	int x2 = safe_int("x2", argv[6], argv);
	int y2 = safe_int("y2", argv[7], argv);
	int z2 = safe_int("z2", argv[8], argv);
	
	const int scale = 3;

	const int width = 192*scale;
	const int height = 108*scale;

	//int size = 2;
	//hitable* worl[size];

	//worl[0] = new triangle(vec3(20,0,0),vec3(-20,0,0),vec3(0,40,0),new diffuse(vec3(0.9,0.3,0.3)));
	//worl[size - 1] = new sphere(vec3(0,-100.5,-1),100.0f,new diffuse(vec3(0.8,0.8,0)));

	//std::vector<hitable *> wor = random_scene();

	vector<hitable*> worl;
	vec3 minb = vec3(1.0e+10,1.0e+10,1.0e+10);
	vec3 maxb = vec3(-1.0e+10,-1.0e+10,-1.0e+10);
	read_stl(filename,worl,minb,maxb);
	cout << filename.substr(13,filename.size()) << " read" << endl;
	//worl.push_back(new triangle(vec3(20,20,0),vec3(-20,20,0),vec3(0,40,0),new diffuse(vec3(0.9,0.3,0.3))));
	worl.push_back(new sphere(vec3(0, -1000, 0), 990, new diffuse(vec3(0.5, 0.5, 0.5))));
    cout << worl.size()<< " triangles detected in " << filename.substr(13,filename.size()) << endl;

	//BVH world = BVH(wor, wor.size(), vec3(-11, -3, -11), vec3(11, 11, 11));
	BVH world = BVH(worl, worl.size(), minb, maxb);
	std::cout << "Bounding Volume Hierarchy Tree made" << std::endl;
	//hitable_list world = hitable_list(wor);

	vec3 origin = vec3(x,y,z);
	vec3 lookat = vec3(x2,y2,z2);
	//vec3 pixels[width*height];
	camera cam = camera(origin, lookat, 65, float(width) / float(height));
	float u, v;

	set<hitable*> smolworld;
	//hitable_list smol;

	std::ofstream file;
	file.open("../images/output.ppm");
	file << "P3\n" << width << " " << height << "\n255\n";

	cout << "Starting to raytrace image of size "<< height << " by " << width << "..." << endl;


	for (int i = height - 1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			vec3 col = vec3(0, 0, 0);
			u = float(j) / float(width);
			v = float(i) / float(height);
			
			ray testRay = cam.get_ray(u,v);
			smolworld = world.hit(testRay,0,2.4e+30);

			//if(smolworld.size() > 1)cout << smolworld.size() << " objects in this pixel: (" <<height -1 -i <<","<<j<<")"<< endl;
			

			for (int s = 0; s < rays_per_pixel; s++)
			{
				u = float(j + ran()) / float(width);
				v = float(i + ran()) / float(height);
				ray r = cam.get_ray(u, v);
				col = col + blend(r, 1, world);
			}
			col /= rays_per_pixel;
			col.x = sqrt(col.x);
			col.y = sqrt(col.y);
			col.z = sqrt(col.z);
			col *= 255.99f;
			file << int(col.x) << " " << int(col.y) << " " << int(col.z) << "\n";
			//if((height-1-i)+j % 1000 == 0)cout << (height-1-i)*width + j << " pixels done" << endl;
			//pixels[(height-1 -i)*width + j] = vec3(int(col.x),int(col.y),int(col.z));
		}cout << i << " lines to go" << endl;
	}
	/*
	std::ofstream file;
	file.open("hell.ppm");
	file << "P3\n" << width << " "<< height << "\n255\n";
	for(int i =0;i<width*height;i++){
		file << pixels[i].x <<" "<< pixels[i].y <<" "<< pixels[i].z <<"\n";
	}
	*/
	std::cout << "Time in seconds: " << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
	std::cout << "Bounced rays: " << boundedRays << std::endl;
}