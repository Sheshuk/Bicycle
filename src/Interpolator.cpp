#include <cmath>
#include "Interpolator.h"
///-------------------------------------------------
double linear_w(int n, double x){
		double dx=std::abs(x-n);
		return (dx>1)?0:1-dx;
}

double lagrange_w(int i, double x,int j0, int j1){
	double result=1;
	for(int j=j0;j<j1;++j){
		if(i!=j)result*=(x-j)/(i-j);
	}
	return result;
};

///-------------------------------------------------
template<size_t N>
double Interpolation::Interpolator<N>::CalcWeight(
	const typename Array<N>::index &idx, 
	const typename Array<N>::point &pnt)
{
	double w=1;
	for(size_t i=0; i<N; ++i){
		int low=arr.Dimensions().Min(i);
		int hig=arr.Dimensions().Max(i);
		w*=W(idx[i],pnt[i],{low,hig});
	}
	return w;
}

template<size_t N>
double Interpolation::Interpolator<N>::Eval(const typename Array<N>::point& pnt){
	typename Array<N>::index lowerIndex,upperIndex;
	for (size_t i = 0; i < N; ++i){
		int central=round(pnt[i]);
		lowerIndex[i]=std::max(central-wBase,  arr.Dimensions().Min(i));
		upperIndex[i]=std::min(central+wBase+1,arr.Dimensions().Max(i));
	}

	double result=0;
	double w=0;
	for(auto& idx : typename Array<N>::Dimension(lowerIndex,upperIndex)) 
	{
		w=CalcWeight(idx,pnt);
		if(w!=0)result+=w*arr(idx);
	}
	return result;
}

///-------------------------------------------------


template class Interpolation::Interpolator<1>;
template class Interpolation::Interpolator<2>;
template class Interpolation::Interpolator<3>;


template class Interpolation::Linear<1>;
template class Interpolation::Linear<2>;
template class Interpolation::Linear<3>;

template class Interpolation::Lagrange<1>;
template class Interpolation::Lagrange<2>;
template class Interpolation::Lagrange<3>;