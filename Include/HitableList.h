#pragma once
class HitableList :
	public Hitable
{
public:
	HitableList() {}
	HitableList(Hitable** L, int N) { List = L; ListSize = N; }
	virtual bool Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec)const;

	Hitable** List;
	int ListSize;
protected:
private:
};

bool HitableList::Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec)const
{
	HitRecord TempRec;
	bool HitAnything = false;
	double ClosestSoFar = TMax;
	for (int i = 0; i < ListSize; i++)
	{
		if (List[i]->Hit(R, TMin, ClosestSoFar, TempRec))
		{
			HitAnything = true;
			ClosestSoFar = TempRec.T;
			Rec = TempRec;
		}
	}
	return HitAnything;
}