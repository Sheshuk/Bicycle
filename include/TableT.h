#ifndef TABLET__H
#define TABLET__H value
#include "Axis.h"
#include "ArrayT.h"
#include "Interpolator.h"
#include <array>

template<size_t N>
class Table
{
public:
	using Axes=std::array<Axis,N>;
	using point=std::array<double,N>;
	using index=std::array<int,N>;
private:
	static index axesSizes(const Axes&);
	static point axesMin(const Axes&);
	static point axesMax(const Axes&);

public:
	Table(const Axes& Ax):axes(Ax),array(axesSizes(Ax)){};
	~Table(){};

	double At (const point &pnt)const{return Nearest(pnt);}
	
	double Nearest (const point &pnt)const{
		return array.Nearest(TransformToLocal(pnt));
	};
	double Linear(const point &pnt)const{
		return (Interpolation::Linear<N>(array)).Eval(TransformToLocal(pnt));
	};
	double Lagrange(const point &pnt)const{
		return (Interpolation::Lagrange<N>(array)).Eval(TransformToLocal(pnt));
	};
	double IDW(const point &pnt)const{
		return (Interpolation::IDW<N>(array)).Eval(TransformToLocal(pnt));
	};
	point TransformToLocal (const point& pnt) const{
		point pntLocal;
		for (size_t i = 0; i < N; ++i)pntLocal[i]=axes[i].IdxFromVal(pnt[i]);
			return pntLocal;
	}
	inline unsigned Nbins(size_t dim) const{return axes[dim].Nbins();}
	inline double  Min(size_t dim) const {return axes[dim].Min();}
	inline double  Max(size_t dim) const {return axes[dim].Max();}
	double MinValue(){return array.MinValue();}
	double MaxValue(){return array.MaxValue();}
	const Axis& GetAxis(size_t n) const{return axes[n];}

	const Array<N>& GetArray() const{return array;}	
	void SetPoint(point idx, double Val){array.AtPoint(TransformToLocal(idx))=Val;}
private:
	Axes axes;
	Array<N> array;
};
#endif

template<size_t N>
typename Table<N>::index Table<N>::axesSizes(const Table<N>::Axes& axes) {
	Table<N>::index result;
	for (size_t i = 0; i < N; ++i)result[i]=axes[i].Nbins();
	return result;
}
