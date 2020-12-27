#pragma once

class Refract
{
public:
	friend inline bool bRefract(const Vec3& V, const Vec3& N, double NiOverNt, Vec3& Refracted);
protected:
private:
};


inline bool bRefract(const Vec3& V, const Vec3& N, double NiOverNt, Vec3& Refracted)
{
	Vec3 UV = UnitVector(V);
	double DT = Dot(UV, N);
	double Discriminant = 1.0 - NiOverNt * NiOverNt * (1 - DT * DT);
	if (Discriminant > 0)
	{
		Refracted = NiOverNt * (UV - N * DT) - N * sqrt(Discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

