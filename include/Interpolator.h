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

		int wBase=0; //!< Weight function half size (base)
	};
//------------------------------
	template<size_t N>
	class Linear: public Interpolator<N>{
	public: 
		Linear(const Array<N>& A):Interpolator<N>(A){};
	protected:
		double W(int n, double x,std::pair<int, int> lims) override{
			double dx=std::abs(x-n);
			return (dx>1)?0:1-dx;
		};
		int wBase=1;
	};

//------------------------------
	template<size_t N>
	class Lagrange: public Interpolator<N>{
	public: 
		Lagrange(const Array<N>& A):Interpolator<N>(A){};
	protected:
		double W(int n, double x,std::pair<int, int> lims) override{
			double result=1;
			for(int j=lims.first;j<=lims.second;++j)
				if(n!=j)result*=(x-j)/(n-j);
			return result;
		};
		int wBase=-1;
	};
}

#endif
