#ifndef AXIS__H
#define AXIS__H value
#include <cstdlib>
class Axis
{
public:
	class Values;
	class Bins;
	class virtual_iterator;
public:
	Axis(size_t NBins,double Min, double Max);
	Axis(const Axis& a);
	double IdxFromVal(double x) const;
	double ValFromIdx(double i) const;
	inline double Min()     const {return min;}
	inline double Max()     const {return max;}
	inline size_t Nbins() const {return nBins;}
	inline double BinSize() const {return (max-min)/(nBins-1);}
	bool isInRange(double x) const;
	double operator()(double x) const{return ValFromIdx(x);}

	void Print() const;
	void PrintRange() const;
	void PrintVal(double x) const;
private:
	size_t nBins;
	double min,max;
};

#include "Axis_Iterator.h"
#endif