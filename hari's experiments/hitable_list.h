#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"
#include "ray.h"
#include <vector>

class hitable_list{
	public:
		std::vector<hitable*> list;
		int size;
		hitable_list(){}
		hitable_list(std::vector<hitable*> l){list = l;size = l.size();}
		virtual bool hit(ray& r,float t_min,float t_max,hit_record& rec) const;
};

bool hitable_list::hit(ray& r,float t_min,float t_max,hit_record& rec) const {
	hit_record hits[size];
	int closest_hit;
	bool hit_anything = false;
	double closest_t = t_max;
	for(int i = 0;i<size;i++){
		if(list[i]->hit(r,t_min,t_max,hits[i])){	
			hit_anything = true;
			if(hits[i].t < closest_t){
				closest_t = hits[i].t;
				closest_hit = i;
			}
		}
	}
	if(hit_anything){
		rec = hits[closest_hit];
		return true;
	}
	return false;
}

#endif
