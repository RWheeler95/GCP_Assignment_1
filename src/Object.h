#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Ray.h"

struct ObjectIntersections
{
	float t;
	glm::vec3 p;
	glm::vec3 normal;
};

class Object
{
private:



public:

	virtual bool Intersections(const Ray& r, float t_min, float t_max, ObjectIntersections& inter) const = 0;

};
#endif