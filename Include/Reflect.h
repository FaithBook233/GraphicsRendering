#pragma once

class Reflect
{
public:
	friend inline Vec3 ReflectRay(const Vec3& V, const Vec3& N);
protected:
private:
};

inline Vec3 ReflectRay(const Vec3& V, const Vec3& N)
{
	return V - 2 * Dot(V, N) * N;
}