#include <cstdio>
#include "Axis.h"

Axis::Axis(size_t NBins,double Min, double Max):
{

};

Axis::Axis(const Axis& a):
nBins(a.nBins),min(a.min),max(a.max){

}

double Axis::IdxFromVal(double x) const{
    if(!isInRange(x))throw MR_ValOutOfRange(x,min,max);
	return  (x-min)*double(nBins-1)/(max-min);
};
double Axis::ValFromIdx(double i) const{
    if(i>nBins || i<0)throw MR_IdxOutOfRange(i,0,nBins);
	return  min+i*(max-min)/double(nBins-1);
}
bool Axis::isInRange(double x) const{
	return (x>min)==(x<max)||(x==min)||(x==max);
}


void Axis::Print() const{
	printf("Axis: %d bins [%5.4f<= x <=%5.4f] - bin size=%g\n",nBins,min,max,BinSize());
}

