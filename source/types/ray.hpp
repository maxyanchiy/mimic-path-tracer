#pragma once
#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray{
public:
	ray(const point3& origin, const vec3 direction) : 
		orig(origin), dir(direction)
	{}

	const point3 origin() { return orig; }
	const vec3 direction() { return dir; }
	const point3 at(const double t) {
		return orig + t * dir;
	}

public:
	point3 orig;
	vec3 dir;
};
#endif // !RAY_H
