#include "Tracer.h"

bool Tracer::Intersections(const Ray & r, float t_min, float t_max, ObjectIntersections & inter, std::vector<std::shared_ptr<Object>> obj) const
{
	ObjectIntersections rootInter;
	bool AnyIntersections = false;
	float Nearest = t_max;
	for (int i = 0; i < obj.size(); i++)
	{
		if (obj.at(i)->Intersections(r, t_min, Nearest, rootInter))
		{
			AnyIntersections = true;
			Nearest = rootInter.t;
			inter = rootInter;
		}
	}
	
	return AnyIntersections;
}
