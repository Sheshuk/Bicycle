#ifndef ARRAYT_DIMENSION__H
#define ARRAYT_DIMENSION__H value
#include <cstring>
//----------------------------------------------
template<size_t N>
class Array<N>::Dimension{
public:
	class iterator{
			public:
				iterator(const Dimension& Dim, const Array<N>::index &Idx, size_t Pos):
				dimension(Dim),idx(Idx),pos(Pos){}
				bool operator!= (const iterator& other) const{return pos!=other.pos;}
				const iterator operator++();
				const index& operator *(){return idx;}
			private:
				const Dimension& dimension;
				index idx;
				size_t pos;
		};
public:
	Dimension(const index& Lower,const index& Upper):lower(Lower),upper(Upper),length(1){
		for(size_t i=0;i<N;++i){
			sizes[i]=upper[i]-lower[i];
			length*=sizes[i];
		}
	}
	size_t PosFromIdx(const index& idx) const;
	size_t PosFromPnt(const point& idx) const;
	void IdxFromPos(size_t Pos, index& Result) const;
	index IdxFromPos(size_t Pos) const;
	
	inline int operator[](size_t ndim) const {return sizes[ndim];}
	inline int Min(size_t ndim) const {return lower[ndim];}
	inline int Max(size_t ndim) const {return upper[ndim];}
	size_t Length() const {return length;}
	iterator begin() const{return iterator(*this,lower,0);}
	iterator end()   const{return iterator(*this,upper,length);}
private:
	index sizes;  //upper index limits 
	index lower;  //lower index limits
	index upper;  //upper index limits
	size_t length;
};

// -------------------------------------------------

template<size_t N>
const typename Array<N>::Dimension::iterator Array<N>::Dimension::iterator::operator++(){
	++pos;
	size_t i=N-1;
	++idx[i];
	while(idx[i]>=dimension.upper[i] && i>0){
		idx[i]=dimension.lower[i];
		++idx[i-1];
		--i;
	}
	return *this;
}


template<size_t N>
size_t Array<N>::Dimension::PosFromIdx(const index& idx) const {
	size_t result=0;
	for(size_t i = 0; i < N; ++i)
	{
		if(idx[i]<lower[i]||idx[i]>=upper[i])throw MR_out_of_range(idx[i],lower[i],upper[i]);
		result=result*sizes[i]+idx[i]-lower[i];
	}
	return result;
}

template<size_t N>
size_t Array<N>::Dimension::PosFromPnt(const point& pnt) const {
	size_t result=0;
	for(size_t i = 0; i < N; ++i)
	{
		int idx=round(pnt[i]);
		if(idx<lower[i]||idx>=upper[i])throw MR_out_of_range(idx,lower[i],upper[i]);
		result=result*sizes[i]+idx-lower[i];
	}
	return result;
}


template<size_t N>
void Array<N>::Dimension::IdxFromPos(size_t Pos, Array<N>::index& Result) const
{	
	for(size_t i = N-1; i >=1; --i){
		Result[i]=Pos%sizes[i];
		Pos/=sizes[i];
	}
	Result[0]=Pos;
	for(size_t i = 0; i<N; ++i)Result[i]+=lower[i];
};

template<size_t N>
typename Array<N>::index Array<N>::Dimension::IdxFromPos(size_t Pos) const{
	Array<N>::index result;
	IdxFromPos(Pos,result);
	return result;
}
#endif