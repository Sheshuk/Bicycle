#ifndef ARRAYT__H
#define ARRAYT__H value

#include <cmath>
#include <array>
#include <algorithm>
#include <functional>
#include "MRexception.h"

//----------------------------------------------
template<size_t N>
class Array
{
public:
	typedef std::array<int,N> index;
	typedef std::array<double,N> point;
	class Dimension;
	class iterator;
public:
	Array(const Dimension& dims):dimension(dims),data(0){data=new double[Length()]();}
	Array(const index& Sizes):dimension(index{0},Sizes),data(0){data=new double[Length()]();}
	~Array(){if(data)delete[] data;}
	
	double Nearest(const point& pnt) const;
	double Eval(const point& pnt, std::function<double(int, double)> w=0, int width=0) const;
	
	inline size_t Length()   const {return dimension.Length();}
	inline int Size(size_t Naxis) const {return dimension[Naxis];}
	inline const Dimension& Dimensions()const{return dimension;}
	inline double& operator ()(const index& Idx)      {return Value(Idx);}
	inline double  operator ()(const index& Idx) const{return Value(Idx);}
	inline double& AtPoint(const point& Pnt)      {return Value(Pnt);}

	inline size_t Position (const index& Idx)const{return dimension.PosFromIdx(Idx);}
	inline size_t PositionP(const point& Idx)const{return dimension.PosFromPnt(Idx);}
	inline index  Index(size_t Pos) const{return dimension.IdxFromPos(Pos);}

	iterator begin() const{return iterator(this,0);}
	iterator end()   const{return iterator(this,dimension.Length());}

	double operator*(const Array<N> other) const;
protected:
	double& Value(const index& Idx) const{return data[Position (Idx)];}
	double& Value(const point& Pnt) const{return data[PositionP(Pnt)];}
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
	return Value(pnt0);
}

template<size_t N>
double Array<N>::operator*(const Array<N> other) const{
	if(length!=other.length)throw MR_length_mismatch(length,other.length);
	double result=0;
	for(size_t i=0; i<length;++i){
		result+=data[i]*other.data[i];
	}
	return result;
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
double Array<N>::Eval(const point& pnt, std::function<double(int, double)> w, int base) const{
	if(w==0)return Nearest(pnt);
	
	index lowerIndex,upperIndex;
	for (size_t i = 0; i < N; ++i){
		int central=round(pnt[i]);
		lowerIndex[i]=std::max(central-base,0);
		upperIndex[i]=std::min(central+base+1,dimension[i]);
	}
	
	double result=0;
	for(auto &idx: Array<N>::Dimension(lowerIndex,upperIndex)){
		double weight=1;
		for(size_t i=0;i<N;++i){
			weight*=w(idx[i],pnt[i]);
			// if(weight==0)break;
		}
		if(weight)result+=weight*Value(idx);
	}
	return result;
}


#endif
