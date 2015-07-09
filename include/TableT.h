#ifndef TABLET__H
#define TABLET__H value
#include "Axis.h"
#include "ArrayT.h"
#include <array>

template<size_t N>
class Table
{
public:
	using Axes=std::array<Axis,N>;
	using point=std::array<double,N>;
	using index=std::array<int,N>;
public:
	static index axesSizes(const Axes&);
	static point axesMin(const Axes&);
	static point axesMax(const Axes&);

public:
	Table(const Axes& Ax):axes(Ax),array(axesSizes(Ax)){};
	~Table(){};

	template<template<size_t>class T> double Eval(const point &pnt)const {return T<N>(array).Eval(TransformToLocal(pnt));}

	point TransformToLocal (const point& pnt) const;
	point TransformToGlobal (const point& pnt) const;
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

template<size_t N>
typename Table<N>::index Table<N>::axesSizes(const Table<N>::Axes& axes) {
	Table<N>::index result;
	for (size_t i = 0; i < N; ++i)result[i]=axes[i].Nbins();
	return result;
}

template<size_t N>
typename Table<N>::point Table<N>::TransformToLocal (const typename Table<N>::point& pnt) const{
		typename Table<N>::point result;
		for (size_t i = 0; i < N; ++i)result[i]=axes[i].IdxFromVal(pnt[i]);
			return result;
	}

template<size_t N>
typename Table<N>::point Table<N>::TransformToGlobal (const typename Table<N>::point& pnt) const{
		typename Table<N>::point result;
		for (size_t i = 0; i < N; ++i)result[i]=axes[i].ValFromIdx(pnt[i]);
			return result;
	}
#endif
