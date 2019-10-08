#include <iostream>
using namespace std;

int main(){
	int width = 200;
	int height = 100;
	float r,g,b=0.2;
	int ir,ig,ib = int(b*255.0);
	cout << "P3\n" << width << " "<< height << "\n255\n";
	for(int i = 0;i<height;i++){
		for(int j=0;j<width;j++){
			r = float(i)/float(height);
			g = float(j)/float(width);
			ir = int(r*255.0);
			ig = int(g*255.0);
			cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
