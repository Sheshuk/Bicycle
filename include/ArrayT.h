#ifndef ARRAYT__H
#define ARRAYT__H value

#include <cmath>
#include <array>
#include <functional>
#include "MRexception.h"

class Interpolator;
//----------------------------------------------
template<size_t N>
class Array
{
public:
	typedef std::array<size_t,N> index;
	typedef std::array<double,N> point;
	class Dimension;
	class iterator;
public:
	Array(const index& Sizes):dimension(Sizes),data(0){data=new double[Length()]();}
	~Array(){if(data)delete[] data;}
	
	double Nearest(const point& pnt) const;
	double Eval(const point& pnt, std::function<double(size_t, double)> w=0) const;
	
	inline size_t Length()   const {return dimension.Length();}
	inline size_t Size(size_t Naxis) const {return dimension[Naxis];}
	inline const Dimension& Dimensions(){return dimension;}

	inline double& operator ()(const index& Idx)      {return at(Idx);}
	inline double  operator ()(const index& Idx) const{return at(Idx);}

	inline size_t Position(const index& Idx)const{return dimension.PosFromIdx(Idx);}
	inline index  Index(size_t Pos) const{return dimension.IdxFromPos(Pos);}

	iterator begin() const{return iterator(this,0);}
	iterator end()   const{return iterator(this,dimension.Length());}

protected:
	double& at(const index& Idx) const{return data[Position(Idx)];}
protected:	
	const Dimension dimension;
	double * data;
	size_t length;
};

#include "ArrayT_dimension.h"
#include "ArrayT_Iterator.h"
//--------------------------------Array class implementation-----------------------------


template<size_t N>
double Array<N>::Nearest(const point& pnt) const{
	index pnt0;
	for (size_t i = 0; i < N; ++i)
		pnt0[i]=round(pnt[i]);
	return at(pnt0);
}

/**
 * @brief general interpolation method
 * @details Calculate interpolated value in point pnt, using weight function, provided by user
 * 
 * @param pnt Point where we need to get value
 * @param w Function double w(size_t n, double x), which calculates 
 * the weight of node n for point with coordinate x. This function is used for each axis
 * 
 * @return interpolated value
 */
template<size_t N>
double Array<N>::Eval(const point& pnt, std::function<double(size_t, double)> w) const{
	if(w==0)return Nearest(pnt);
	double result=0;
	for(auto &idx: dimension){
		double weight=1;
		for(size_t dim=0;dim<N;++dim){
			weight*=w(idx[dim],pnt[dim]);
			// if(weight==0)break;
		}
		if(weight)result+=weight*at(idx);
	}
	return result;
}


#endif
