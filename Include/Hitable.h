#pragma once
#include"Ray.h"

class Material;

struct HitRecord
{
	double T;
	Vec3 P;
	Vec3 Normal;
	Material* MatPtr;
};
class Hitable
{
public:
	//´¿Ðéº¯Êý
	virtual bool Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec) const = 0;
protected:
private:
};