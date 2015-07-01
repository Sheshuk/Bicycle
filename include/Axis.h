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
	double IdxFromVal(double x) const {return  (x-min)*double(nBins-1)/(max-min);}
	double ValFromIdx(double i) const {return  min+i*(max-min)/double(nBins-1); }
	double Min()     const {return min;}
	double Max()     const {return max;}
	double Range()	 const {return max-min;}
	size_t Nbins() const {return nBins;}
	double BinSize() const {return (max-min)/(nBins-1);}
	bool isInRange(double x) const{return (x>min)==(x<max)||(x==min)||(x==max);};
	double operator()(double x) const{return ValFromIdx(x);}
	void Print(){printf("Axis: range=%4.3g/%ld bins [%5.2g<= x <=%5.2g] - bin size=%g\n",Range(),nBins,min,max,BinSize());};
private:
	size_t nBins;
	double min,max;
};

#include "Axis_Iterator.h"
#endif