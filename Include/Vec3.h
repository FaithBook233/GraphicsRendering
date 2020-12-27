#pragma once
/*
	Vec3类为空间三维坐标或RGB颜色的抽象类
	E[3]数组为向量的具体数值

*/
#include<iostream>
#include<stdlib.h>
#include <Math.h>
class Vec3
{
public:
	Vec3() {};
	Vec3(double E0, double E1, double E2)
	{
		E[0] = E0;
		E[1] = E1;
		E[2] = E2;
	}
	//返回单个向量的值
	inline double X() const { return E[0]; }
	inline double Y() const { return E[1]; }
	inline double Z() const { return E[2]; }
	inline double R() const { return E[0]; }
	inline double G() const { return E[1]; }
	inline double B() const { return E[2]; }

	inline const Vec3& operator+() const { return *this; }
	inline Vec3 operator-() const { return Vec3(-E[0], -E[1], -E[2]); }
	inline double operator[](int i)const { return E[i]; }
	inline double& operator[](int i ) { return E[i]; }

	inline Vec3& operator+=(const Vec3 &V2);
	inline Vec3& operator-=(const Vec3 &V2);
	inline Vec3& operator*=(const Vec3 &V2);
	inline Vec3& operator/=(const Vec3 &V2);
	inline Vec3& operator*=(const double T);
	inline Vec3& operator/=(const double T);

	inline double Vec3Length() const {
		return sqrt(E[0] * E[0] + E[1] * E[1] + E[2] * E[2]);
	 } 
	inline double SquaredLength() const {
		return E[0] * E[0] + E[1] * E[1] + E[2] * E[2];
	 }
	inline void  MakeUnitVector();

	friend inline Vec3 UnitVector(Vec3 V);

	friend inline std::istream& operator>>(std::istream& IS, Vec3& T);
	friend inline std::ostream& operator<<(std::ostream& OS, const Vec3& T);
	friend inline Vec3 operator+(const Vec3& V1, const Vec3& V2);
	friend inline Vec3 operator-(const Vec3& V1, const Vec3& V2);
	friend inline Vec3 operator*(const Vec3& V1, const Vec3& V2);
	friend inline Vec3 operator/(const Vec3& V1, const Vec3& V2);
	friend inline Vec3 operator*(double T, const Vec3& V);
	friend inline Vec3 operator/(const Vec3& V, double T);
	friend inline Vec3 operator*(const Vec3& V, double T);
	friend inline double Dot(const Vec3& V1, const Vec3& V2);
	friend inline Vec3 Cross(const Vec3& V1, const Vec3& V2);



	double E[3];

protected:
private:
	
};

//以下为类的非成员函数
inline std::istream& operator>>(std::istream& IS, Vec3& T)
{
	IS >> T.E[0] >> T.E[1] >> T.E[2];
	return IS;
}
inline std::ostream& operator<<(std::ostream& OS, const Vec3& T)
{
	OS << T.E[0] << " " << T.E[1] << " " << T.E[2];
	return OS;
}
inline void Vec3::MakeUnitVector()
{
	double k = 1.0 / sqrt(E[0] * E[0] + E[1] * E[1] + E[2] * E[2]);
	E[0] *= k;
	E[1] *= k;
	E[2] *= k;
}

inline Vec3 operator+(const Vec3& V1, const Vec3& V2)
{
	return Vec3(V1.E[0] + V2.E[0], V1.E[1] + V2.E[1], V1.E[2] + V2.E[2]);
}
inline Vec3 operator-(const Vec3& V1, const Vec3& V2)
{
	return Vec3(V1.E[0] - V2.E[0], V1.E[1] - V2.E[1], V1.E[2] - V2.E[2]);
}
inline Vec3 operator*(const Vec3& V1, const Vec3& V2)
{
	return Vec3(V1.E[0] * V2.E[0], V1.E[1] * V2.E[1], V1.E[2] * V2.E[2]);
}
inline Vec3 operator/(const Vec3& V1, const Vec3& V2)
{
	return Vec3(V1.E[0] / V2.E[0], V1.E[1] / V2.E[1], V1.E[2] / V2.E[2]);
}

inline Vec3 operator*(double T, const Vec3& V)
{
	return Vec3(T * V.E[0], T * V.E[1], T * V.E[2]);
}
inline Vec3 operator/(const Vec3& V, double T)
{
	return Vec3(V.E[0]/T,V.E[1]/T,V.E[2]/T);
}
inline Vec3 operator*(const Vec3& V, double T)
{
	return Vec3(T * V.E[0], T * V.E[1], T * V.E[2]);
}
//乘
inline double Dot(const Vec3& V1, const Vec3& V2)
{
	return V1.E[0] * V2.E[0] + V1.E[1] * V2.E[1] + V1.E[2] * V2.E[2];
}

/*(a1,a2,a3) 运算符(b1,b2,b3)
 =(a2*b3 - a3*b2,-(a1*b3 - a3*b1),a1*b2 - a2*b1)

 */
inline Vec3 Cross(const Vec3& V1, const Vec3& V2)
{
	return Vec3(
		(V1.E[1] * V2.E[2] - V1.E[2] * V2.E[1]),
		(-(V1.E[0] * V2.E[2] - V1.E[2] * V2.E[0])),
		(V1.E[0] * V2.E[1] - V1.E[1] * V2.E[0])
	);
}
inline Vec3& Vec3::operator+=(const Vec3& V)
{
	E[0] += V.E[0];
	E[1] += V.E[1];
	E[2] += V.E[2];
	return *this;
}
inline Vec3& Vec3::operator*=(const Vec3& V)
{
	E[0] *= V.E[0];
	E[1] *= V.E[1];
	E[2] *= V.E[2];
	return *this;
}
inline Vec3& Vec3::operator-=(const Vec3& V)
{
	E[0] -= V.E[0];
	E[1] -= V.E[1];
	E[2] -= V.E[2];
	return *this;
}
inline Vec3& Vec3::operator/=(const Vec3& V)
{
	E[0] /= V.E[0];
	E[1] /= V.E[1];
	E[2] /= V.E[2];
	return *this;
}
inline Vec3& Vec3::operator*=(const double T)
{
	E[0] *= T;
	E[1] *= T;
	E[2] *= T;
	return *this;
}
inline Vec3& Vec3::operator/=(const double T)
{
	double K = 1.0 / T;
	E[0] *= K;
	E[1] *= K;
	E[2] *= K;
	return *this;
}

//向量/模长 = 单位方向向量
//这里可能有问题
inline Vec3 UnitVector(Vec3 V)
{
	return V / V.Vec3Length();
}