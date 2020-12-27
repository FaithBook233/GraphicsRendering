#pragma once
#include "Vec3.h"
#include"Random.h"
class Ray
{
public:
	Ray() {}
	Ray(const Vec3& _A, const Vec3& _B) { A = _A; B = _B; }//光线初始化
	Vec3 Origin()const { return A; }//获取起始点坐标
	Vec3 Direction()const { return B; }//获取方向向量（非单位方向向量）
	Vec3 PointAtParameter(double T)const { return A + B * T; }//P(t) = A +T *B;T浮动

	friend inline Vec3 RandomInUnitSphere();

	Vec3 A;	//起始点坐标
	Vec3 B;//
protected:
private:
	
};

Vec3 RandomInUnitSphere() {
	Vec3 P;
	do {
		P = 2.0 * Vec3(Rand01(), Rand01(), Rand01()) - Vec3(1, 1, 1);
	} while (P.SquaredLength() >= 1.0);
	return P;
}
