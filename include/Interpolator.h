#ifndef INTERPOLATOR__H
#define INTERPOLATOR__H value
#include <algorithm>
#include "ArrayT.h"

namespace Interpolation{
	template<size_t N>
	class Linear{
	public:
		Linear(const Array<N>& A):arr(A){};
		~Linear(){};
		double Eval(const typename Array<N>::point& pnt);
	protected:
		double CalcWeight(const typename Array<N>::index &idx, const typename Array<N>::point &pnt);
		const Array<N> &arr;
	};

	template<size_t N>
	class Lagrange{
	public:
		Lagrange(const Array<N>& A):arr(A){};
		~Lagrange(){};
		double Eval(const typename Array<N>::point& pnt);
	protected:
		double CalcWeight(const typename Array<N>::index &idx, const typename Array<N>::point &pnt);
		const Array<N> &arr;
	};
}

#endif
