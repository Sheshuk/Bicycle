#ifndef INTERPOLATOR__H
#define INTERPOLATOR__H value
#include <algorithm>
#include "ArrayT.h"
/**
 * @brief virtual interpolator class
 */	
namespace Interpolation{

	template<size_t N>
	class VirtualInterpolator{
	public:
		VirtualInterpolator(const Array<N>& A):arr(A){};
		virtual ~VirtualInterpolator(){};
		virtual double Eval(const typename Array<N>::point& pnt) = 0;
	protected:
		const Array<N> &arr;
	};
//------------------------------
	template<size_t N>
	class Nearest: public VirtualInterpolator<N>{
	public:
		Nearest(const Array<N>& A):VirtualInterpolator<N>(A){}
		double Eval(const typename Array<N>::point& pnt) override { return this->arr.Eval(pnt);}
	};
//------------------------------
	template<size_t N>
	class WeightBased: public VirtualInterpolator<N>{
	public:
		WeightBased(const Array<N>& A, int BaseSize):VirtualInterpolator<N>(A),wBase(BaseSize){}
		double Eval(const typename Array<N>::point& pnt) override;
	protected:
		virtual double W(int n, double x,std::pair<int, int> lims) = 0;
		double CalcWeight(const typename Array<N>::index &idx, const typename Array<N>::point &pnt);
	protected:
		int wBase=0; //!< Weight function half size (base)
	};
//------------------------------
	template<size_t N>
	class Linear: public WeightBased<N>{
	public: 
		Linear(const Array<N>& A):WeightBased<N>(A,1){};
	protected:
		double W(int n, double x,std::pair<int, int> lims) override{
			double dx=std::abs(x-n);
			return (dx>1)?0:1-dx;
		};
	};
//------------------------------
	template<size_t N>
	class IDW: public WeightBased<N>{
	public: 
		IDW(const Array<N>& A):WeightBased<N>(A,3){};
	protected:
		double W(int n, double x,std::pair<int, int> lims) override{
			double dx=std::abs(x-n);
			return exp(-5*dx);
		};
	};
//------------------------------
	template<size_t N>
	class Lagrange: public WeightBased<N>{
	public: 
		Lagrange(const Array<N>& A):WeightBased<N>(A,-1){};
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
double Interpolation::WeightBased<N>::Eval(const typename Array<N>::point& pnt){
	typename Array<N>::index lowerIndex,upperIndex;
	for (size_t i = 0; i < N; ++i){
		if(wBase<0){
			lowerIndex[i]=this->arr.Dimensions().Min(i);
			upperIndex[i]=this->arr.Dimensions().Max(i);
		}
		else{
			int central=round(pnt[i]);
			lowerIndex[i]=std::max(central-wBase,  this->arr.Dimensions().Min(i));
			upperIndex[i]=std::min(central+wBase+1,this->arr.Dimensions().Max(i));
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
		result+=w*this->arr(idx);
	}
	if(sumW!=0)result/=sumW;
	return result;
}


template<size_t N>
double Interpolation::WeightBased<N>::CalcWeight(
	const typename Array<N>::index &idx, 
	const typename Array<N>::point &pnt)
{
	double w=1;
	for(size_t i=0; i<N; ++i){
		int low=this->arr.Dimensions().Min(i);
		int hig=this->arr.Dimensions().Max(i);
		w*=W(idx[i],pnt[i],{low,hig});
	}
	return w;
}
#endif
