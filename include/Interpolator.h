#ifndef INTERPOLATOR__H
#define INTERPOLATOR__H value
#include <algorithm>
#include "ArrayT.h"
/**
 * @brief virtual interpolator class
 */	
namespace Interpolation{

	template<size_t N>
	class Interpolator
	{
	public:
		Interpolator(const Array<N>& A):arr(A){};
		virtual ~Interpolator(){};
		double Eval(const typename Array<N>::point& pnt);
	protected:
		virtual double W(int n, double x,std::pair<int, int> lims) = 0;
		double CalcWeight(const typename Array<N>::index &idx, const typename Array<N>::point &pnt);
		const Array<N> &arr;
	protected:
		int wBase=0; //!< Weight function half size (base)
	};
//------------------------------
	template<size_t N>
	class Linear: public Interpolator<N>{
	public: 
		Linear(const Array<N>& A):Interpolator<N>(A){this->wBase=1;};
	protected:
		double W(int n, double x,std::pair<int, int> lims) override{
			double dx=std::abs(x-n);
			return (dx>1)?0:1-dx;
		};
	};
//------------------------------
	template<size_t N>
	class IDW: public Interpolator<N>{
	public: 
		IDW(const Array<N>& A):Interpolator<N>(A){this->wBase=3;};
	protected:
		double W(int n, double x,std::pair<int, int> lims) override{
			double dx=std::abs(x-n);
			return exp(-5*dx);
		};
	};
//------------------------------
	template<size_t N>
	class Lagrange: public Interpolator<N>{
	public: 
		Lagrange(const Array<N>& A):Interpolator<N>(A){this->wBase=-1;};
	protected:
		double W(int n, double x,std::pair<int, int> lims) override{
			double result=1;
			for(int j=lims.first;j<=lims.second;++j)
				if(n!=j)result*=(x-j)/(n-j);
			return result;
		};
	};
}
//----------------------------------------------------
//Methods definition:
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
		if(wBase<0){
			lowerIndex[i]=arr.Dimensions().Min(i);
			upperIndex[i]=arr.Dimensions().Max(i);
		}
		else{
			int central=round(pnt[i]);
			lowerIndex[i]=std::max(central-wBase,  arr.Dimensions().Min(i));
			upperIndex[i]=std::min(central+wBase+1,arr.Dimensions().Max(i));
		}
	}

	double result=0;
	double w=0;
	double sumW=0;
	for(auto& idx : typename Array<N>::Dimension(lowerIndex,upperIndex)) 
	{
		w=CalcWeight(idx,pnt);
		if(w==0)continue;
		sumW+=w;
		result+=w*arr(idx);
	}
	if(sumW!=0)result/=sumW;
	return result;
}
#endif
