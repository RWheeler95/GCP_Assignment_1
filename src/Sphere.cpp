#include "Sphere.h"

bool Sphere::Intersections(const Ray & r, float t_min, float t_max, ObjectIntersections & inter) const
{
	glm::vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float root = (-b - sqrt(b * b - a * c)) / a;

		if (root > t_min && root < t_max)
		{
			inter.t = root;
			inter.p = r.p(inter.t);
			inter.normal = (inter.p - center) / radius;

			return true;
		}

		root = (-b + sqrt(b * b - a * c)) / a;

		if (root > t_min && root < t_max)
		{
			inter.t = root;
			inter.p = r.p(inter.t);
			inter.normal = (inter.p - center) / radius;

			return true;
		}
	}
	
	return false;
}
