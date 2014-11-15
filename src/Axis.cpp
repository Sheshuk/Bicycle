#include <cstdio>
#include "Axis.h"

Axis::Axis(size_t NBins,double Min, double Max):
nBins(NBins),min(Min),max(Max){

};

Axis::Axis(const Axis& a):
nBins(a.nBins),min(a.min),max(a.max){

}

double Axis::IdxFromVal(double x) const{
	return  (x-min)*double(nBins-1)/(max-min);
};
double Axis::ValFromIdx(double i) const{
	return  min+i*(max-min)/double(nBins-1);
}
bool Axis::isInRange(double x) const{
	return (x>min)==(x<max)||(x==min)||(x==max);
}


void Axis::Print() const{
	printf("Axis: %d bins [%5.4f<= x <=%5.4f] - bin size=%g\n",nBins,min,max,BinSize());
}

void Axis::PrintRange() const{
	for (size_t i = 0; i < nBins; ++i)PrintVal(i);
}
void Axis::PrintVal(double x) const {
	printf("Axis[%2.2f]= %f\n",x,(*this)(x));
}

