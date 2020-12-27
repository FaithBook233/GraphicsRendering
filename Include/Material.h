/*
	**�ṩ����
	
*/

#pragma once
#include"Reflect.h"
#include "Refract.h"
#include"Random.h"

double Schlick(double Cosine, double Ref)
{
	double R0 = (1 - Ref) / (1 + Ref);
	R0 = R0 * R0;
	return R0 + (1 - R0) * pow((1 - Cosine), 5);
}




/*
	���ʳ�����
*/
class Material
{
public:
	//���麯��
	virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Vec3& Attenuation, Ray& Scattered) const = 0;

	
protected:
private:
};

/*
	���������
*/
class Lambertian :
	public Material
{
public:
	Lambertian(const Vec3& A) :Albedo(A) {}
	virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Vec3& Attenuation, Ray& Scattered) const
	{
		Vec3 Target = Rec.P + Rec.Normal + RandomInUnitSphere();
		Scattered = Ray(Rec.P, Target - Rec.P);
		Attenuation = Albedo;
		return true;
	}
	Vec3 Albedo;
protected:
private:
};

/*
	��������
*/
class Metal :
	public Material
{
public:
	Metal(const Vec3& A,double F) :Albedo(A) 
	{
		if (F < 1)Fuzz = F;
		else Fuzz = 1;
	}
	virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Vec3& Attenuation, Ray& Scattered) const
	{
		Vec3 Reflected = ReflectRay(UnitVector(RIn.Direction()), Rec.Normal);
		Scattered = Ray(Rec.P, Reflected+ Fuzz*RandomInUnitSphere());
		Attenuation = Albedo;
		return (Dot(Scattered.Direction(), Rec.Normal) > 0);
	}

	Vec3 Albedo;
	double Fuzz;
protected:
private:
};




class Dielectric:
	public Material
{
public:
	Dielectric(double Ri) :RefIdx(Ri) {}
	virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Vec3& Attenuation, Ray& Scattered) const
	{
		Vec3 OutwardNormal;
		Vec3 Reflected = ReflectRay(RIn.Direction(), Rec.Normal);
		double NiOverNt;

		//��������͸����ɫ
		Attenuation = Vec3(1.0, 1.0, 1.0);
		Vec3 Refracted;
		double ReflectProb;
		double Cosine;
		if (Dot(RIn.Direction(),Rec.Normal) >0)
		{
			OutwardNormal = -Rec.Normal;
			NiOverNt = RefIdx;

			//��
			Cosine = Dot(RIn.Direction(), Rec.Normal) / RIn.Direction().Vec3Length();
			
			//����ӵ�
			//Cosine = sqrt(1 - RefIdx * RefIdx * (1 - Cosine * Cosine));
		}
		else
		{
			OutwardNormal = Rec.Normal;
			NiOverNt = 1.0/RefIdx;
			Cosine = -Dot(RIn.Direction(), Rec.Normal) / RIn.Direction().Vec3Length();
		}

		if (bRefract(RIn.Direction(),OutwardNormal,NiOverNt,Refracted))
		{
			ReflectProb = Schlick(Cosine, RefIdx);
		}
		else
		{
			//����ȥ����
			Scattered = Ray(Rec.P, Reflected);
			ReflectProb = 1.0;
		}

		if (Rand01() < ReflectProb)
		{
			Scattered = Ray(Rec.P, Reflected);
		}
		else
		{
			Scattered = Ray(Rec.P, Refracted);
		}
		return true;
	}


	friend double Schlick(double Cosine, double RefIdx_);

	double RefIdx;

protected:
private:
};

