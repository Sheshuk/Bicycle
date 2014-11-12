#ifndef AXIS_ITERATOR__H
#define AXIS_ITERATOR__H value
#include "Axis.h"
// interface for making ranged for loops
///------------------------------------------
class axis_VirtualIterator
{
public:
	axis_VirtualIterator(const Axis& A,unsigned Pos):a(A),pos(Pos){};
	bool operator!= (const axis_VirtualIterator& other) const{return (pos!=other.pos);}
	const axis_VirtualIterator& operator++(){++pos;return *this;}
protected:
	const Axis& a;
	unsigned pos;
};
//----------------------------------------------
class axis_IterV:public axis_VirtualIterator
{
public:
	axis_IterV(const Axis& A,unsigned Pos):axis_VirtualIterator(A,Pos){};
	double operator*() const{return a.ValFromIdx(pos);}
};
//----------------------------------------------
class axis_IterB:public axis_VirtualIterator
{
public:
	axis_IterB(const Axis& A,unsigned Pos):axis_VirtualIterator(A,Pos){};
	unsigned operator*() const{return pos;}
};

//----------------------------------------------
class AxisValues
{
public:
	AxisValues(const Axis& Ax):axis(Ax){};
	axis_IterV begin() const{return axis_IterV(axis,0);}
	axis_IterV end()   const{return axis_IterV(axis,axis.Nbins());}
private:
	const Axis& axis;
};
//----------------------------------------------
class AxisBins
{
public:
	AxisBins(const Axis& Ax):axis(Ax){};
	axis_IterB begin() const{return axis_IterB(axis,0);}
	axis_IterB end()   const{return axis_IterB(axis,axis.Nbins());}
private:
	const Axis& axis;
};
//----------------------------------------------
#endif