#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Object.h"

class Sphere : public Object
{
private:

	glm::vec3 center;
	float radius;

public:

	Sphere() { }
	Sphere(glm::vec3 cen, float r) : center(cen), radius(r) { };

	virtual bool Intersections(const Ray& r, float t_min, float t_max, ObjectIntersections& inter) const;

};
#endif