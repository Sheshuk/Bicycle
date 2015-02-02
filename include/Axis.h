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
	Axis(size_t NBins,double Min, double Max):nBins(NBins),min(Min),max(Max){};
	Axis(const Axis& a):nBins(a.nBins),min(a.min),max(a.max){};
	inline double IdxFromVal(double x) const {return  (x-min)*double(nBins-1)/(max-min);}
	inline double ValFromIdx(double i) const {return  min+i*(max-min)/double(nBins-1); }
	inline double Min()     const {return min;}
	inline double Max()     const {return max;}
	inline size_t Nbins() const {return nBins;}
	inline double BinSize() const {return (max-min)/(nBins-1);}
	inline bool isInRange(double x) const{return (x>min)==(x<max)||(x==min)||(x==max);};
	inline double operator()(double x) const{return ValFromIdx(x);}

private:
	size_t nBins;
	double min,max;
};

#include "Axis_Iterator.h"
#endif