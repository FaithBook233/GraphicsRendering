#pragma once

#include <time.h>
#include <stdlib.h>
#include <cstdlib>

class Random
{
public:
	friend inline double Rand01();
	friend inline double RandDbl();
protected:
private:
};
inline double Rand01()
{
	return (rand() % (999 + 1)) / (float)(999 + 1);
}

inline double RandDbl()
{
	return rand() / (RAND_MAX + 1.0);
}