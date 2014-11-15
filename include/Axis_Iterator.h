#ifndef AXIS_ITERATOR__H
#define AXIS_ITERATOR__H value
#include "Axis.h"
// interface for making ranged for loops
///------------------------------------------
class Axis::virtual_iterator
{
public:
	virtual_iterator(const Axis& A,size_t Pos):a(A),pos(Pos){};
	virtual ~virtual_iterator(){};
	// size_t operator*() const=0;
	bool operator!= (const virtual_iterator& other)const{return (pos!=other.pos);}
	const virtual_iterator& operator++(){++pos;return *this;}
protected:
	const Axis& a;
	size_t pos;
};
//----------------------------------------------
class Axis::Values
{
	class iterator:public virtual_iterator{
	public:
		iterator(const Axis& A,size_t Pos):virtual_iterator(A,Pos){};
		double operator*() const{return a.ValFromIdx(pos);}
	};

public:
	Values(const Axis& Ax):axis(Ax){};
	iterator begin() const{return iterator(axis,0);}
	iterator end()   const{return iterator(axis,axis.nBins);}
private:
	const Axis& axis;
};
//----------------------------------------------
class Axis::Bins
{
	class iterator:public virtual_iterator{
	public:
		iterator(const Axis& A,size_t Pos):virtual_iterator(A,Pos){};
		size_t operator*() const{return pos;}
	};

public:
	Bins(const Axis& Ax):axis(Ax){};
	iterator begin() const{return iterator(axis,0);}
	iterator end()   const{return iterator(axis,axis.nBins);}
private:
	const Axis& axis;
};

//----------------------------------------------
#endif