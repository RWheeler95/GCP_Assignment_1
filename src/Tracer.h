#ifndef _TRACER_H_
#define _TRACER_H_

#include <memory>
#include <vector>

#include "Object.h"

class Tracer : public Object
{
private:

	std::vector<std::shared_ptr<Object>> objects;

public:

	Tracer() { }
	bool Intersections(const Ray& r, float t_min, float t_max, ObjectIntersections& inter) const;

};
#endif