#include <cmath>
#include "ray.h"
#define BACKGROUND_COLOR Vector3D(0.5f, 0.5f, 0.5f)

Vector3D combine_colors(Vector3D &a, Vector3D &b) {
	return Vector3D(a.r * b.r, a.g * b.g, a.b * b.b);
}

Vector3D clamp_color(Vector3D &a) {
	return Vector3D(std::min(1.0, a.r),std::min(1.0, a.g), std::min(1.0, a.b));
}

Vector3D refract(const Vector3D& normal, const Vector3D& incident, double n1, double n2) {
	const double n = n1 / n2;
	const double cosI = normal * incident;
	const double sinT2 = n * n * (1.0 - cosI * cosI);
	if (sinT2 > 1.0) {
		return Vector3D(-500, -500, -500);
	}
	return n * incident - (n + sqrt(1.0 - sinT2)) * normal;
}

double Ray::Intersect(Object *obj) {
	return obj->Intersect(OffsetSource(), direction);
}

Ray::Intersection Ray::FindClosestIntersection(Environment& env) {
	Intersection inter;
	inter.obj = NULL;
	inter.dist = INFINITY;
	std::vector<Object*>::iterator it;
	for(it = env.objects.begin(); it != env.objects.end(); ++it) {
		float d = Intersect(*it);
		if(d > 0 && (inter.obj == NULL || inter.dist > d)) {
			inter.obj = *it;
			inter.dist = d;
		}
	}
	return inter;
}

Vector3D Ray::LightTrace(Vector3D position, Vector3D normal, Environment &env, int recursion) {
	if(recursion > MAX_RECURSION) return BACKGROUND_COLOR;
	std::vector<Light*>::iterator it;

	Vector3D color;
	for(it = env.lights.begin(); it != env.lights.end(); ++it) {
		Ray light_ray(position, ((*it)->Position() - position).Normalize());
		float shade = normal * light_ray.direction;
		if(shade < 0) continue;

		Intersection inter = light_ray.FindClosestIntersection(env);
		if(inter.obj == NULL) {
			color = color + shade * (*it)->GetColorAt(position);
		} else {
			continue; // shade = 0
		}
	}
	return color;
}

Vector3D Ray::Refract(Intersection &inter, Environment &env, int recursion) {
	Vector3D position = source + direction * inter.dist;

	double n1, n2;
	if(ior - 1.0 < 1.0e-6) {
		n1 = 1.0;
		n2 = inter.obj->surface().refracao;
	} else {
		n1 = inter.obj->surface().refracao;
		n2 = 1.0;
	}

	Vector3D refract_direction = refract(inter.obj->Normal(position), direction, n1, n2);
	if(refract_direction[0] <= -499) {
		return BACKGROUND_COLOR;
	}

	Ray refraction(position, refract_direction.Normalize());
	refraction.ior = n2;

	return refraction.Trace(env, recursion + 1);
}

Vector3D Ray::Trace(Environment &env, int recursion) {
	if(recursion > MAX_RECURSION) return BACKGROUND_COLOR;
	Intersection inter = FindClosestIntersection(env);
	if(inter.obj == NULL)
		return BACKGROUND_COLOR;

	Vector3D position = source + direction * inter.dist,
			 normal = inter.obj->Normal(position);

	if(normal * direction > 0) normal = -normal;

	Vector3D reflect_direction = direction - 2 *(normal * direction) * normal;
	Vector3D half_reflect = (direction + normal).Normalize();
	Ray reflected_ray = Ray(position, reflect_direction);

	Vector3D object_color = inter.obj->GetColorAt(position),
			 ambient_color = env.ambient_light->Color(),
			 diffuse_color = LightTrace(position, normal, env, recursion),
			 specular_color = reflected_ray.Trace(env, recursion + 1),
			 refraction_color = Refract(inter, env, recursion);

	Vector3D total_color =
			ambient_color * inter.obj->surface().ambiente +
			diffuse_color * inter.obj->surface().difusao;

	total_color = combine_colors(total_color, object_color);
	total_color = total_color
			+ specular_color * inter.obj->surface().especular
				* pow(std::max(0.0, normal * half_reflect), inter.obj->surface().brilho)
			+ refraction_color * inter.obj->surface().transmissao;

	return clamp_color(total_color);
}
