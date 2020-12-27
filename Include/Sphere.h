#pragma once
#include "Hitable.h"
#include"Random.h"
#include "Material.h"
class Sphere :
	public Hitable
{
public:
	Sphere() {}
	Sphere(Vec3 Cen, double R) :Center(Cen), Radius(R) {}; 
	Sphere(Vec3 Cen, double R,Material* Mat) :Center(Cen), Radius(R) ,MatPtr(Mat){};
	virtual bool Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec)const;

	Vec3 Center;
	double Radius;
	Material* MatPtr;
	
protected:
private:
};


bool Sphere::Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec)const
{
	Vec3 OC = R.Origin() - Center;//从球心到射线发射点的向量

	double A = Dot(R.Direction(), R.Direction());
	double B = Dot(OC, R.Direction());
	double C = Dot(OC, OC) - Radius * Radius;
	double Discriminant = B * B - A * C;
	if (Discriminant > 0)
	{
		/*
		注意下面这句原文没有给出，如果不加是个重大错误
		*/
		Rec.MatPtr = MatPtr;
		double Temp = (-B - sqrt(B * B - A * C)) / A;
		if (Temp < TMax && Temp >TMin)
		{
			Rec.T = Temp;
			Rec.P = R.PointAtParameter(Rec.T);
			Rec.Normal = (Rec.P - Center) / Radius;
			return true;
		}
		Temp = (-B + sqrt(B * B - A * C)) / A;
		if (Temp < TMax && Temp >TMin)
		{
			Rec.T = Temp;
			Rec.P = R.PointAtParameter(Rec.T);
			Rec.Normal = (Rec.P - Center) / Radius;
			return true;
		}
	}
	return false;
}
