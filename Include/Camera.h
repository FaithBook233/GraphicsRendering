#pragma once
#include"Ray.h"
#include <corecrt_math_defines.h>
#include"Random.h"

Vec3 RandomInUnitDisk()
{
	Vec3  P;
	do {
		P = 2.0 * Vec3(Rand01(), Rand01(), 0) - Vec3(1, 1, 0);
	} while (Dot(P ,P) >= 1.0);
	return P;
}

class Camera
{
public:
	//VFov为视野（角度）  
	//Aspect为宽/长
	Camera(Vec3 LookFrom,Vec3 LookAt,Vec3 VUP,double VFov,double Aspect,double Aperture,double FocusDist) {	
		LensRadius = Aperture / 2;
		double Theta = VFov * M_PI / 180;
		double HalfHeight = tan(Theta / 2);
		double HalfWidth = Aspect * HalfHeight;
		Origin = LookFrom;
		W = UnitVector(LookFrom - LookAt);
		U = UnitVector(Cross(VUP, W));
		V = Cross(W, U);
		LowerLeftCorner = Origin - U * FocusDist * HalfWidth - V * FocusDist * HalfHeight - W * FocusDist;
		Horizontal = 2*HalfWidth*FocusDist*U;//水平向量，用于计算U
		Vertical = 2*HalfHeight*FocusDist*V;//竖直向量，用于计算V
	}
	Ray GetRay(double S, double T)			
	{
		Vec3 Rd = LensRadius * RandomInUnitDisk();
		Vec3 Offset = U * Rd.X() + V * Rd.Y();
		return Ray(Origin + Offset, LowerLeftCorner + S * Horizontal + T * Vertical - Origin - Offset);
	}

	Vec3 Origin;
	Vec3 LowerLeftCorner;
	Vec3 Horizontal;
	Vec3 Vertical;
	Vec3 U, V, W;
	double  LensRadius;
protected:
private:
};
