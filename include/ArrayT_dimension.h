#ifndef ARRAYT_DIMENSION__H
#define ARRAYT_DIMENSION__H value
//----------------------------------------------
template<size_t N>
class Array<N>::Dimension{
public:
	class iterator{
			public:
				iterator(const Dimension& Dim, size_t Pos):dimension(Dim),pos(Pos){
					dimension.IdxFromPos(pos,idx);
				};
				bool operator!= (const iterator& other) const {return other.pos!=pos;}
				const iterator operator++();
				const Array<N>::index& operator *(){return idx;}
			private:
				const Array<N>::Dimension& dimension;
				size_t pos;
				Array<N>::index idx;
		};
public:
	Dimension(const Array<N>::index& Sizes):sizes(Sizes),length(1){
		for(size_t dim : Sizes)length*=dim;
	}
	
	size_t PosFromIdx(const index& idx) const;
	void IdxFromPos(size_t Pos, Array<N>::index& Result) const;
	Array<N>::index IdxFromPos(size_t Pos) const;
	
	size_t operator[](size_t ndim) const {return sizes[ndim];}

	size_t Length() const {return length;}
	iterator begin() const{return iterator(*this,0);}
	iterator end()   const{return iterator(*this,length);}
private:
	Array<N>::index sizes;
	size_t length;
};

// -------------------------------------------------

template<size_t N>
const typename Array<N>::Dimension::iterator Array<N>::Dimension::iterator::operator++(){
	pos++;
	size_t i=N-1;
	idx[i]++;
	while(idx[i]>=dimension[i] && i>0){
		idx[i]-=dimension[i];
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
		if(idx[i]>=sizes[i])throw MR_out_of_range(idx[i],sizes[i]);
		result=result*sizes[i]+idx[i];
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
};

template<size_t N>
typename Array<N>::index Array<N>::Dimension::IdxFromPos(size_t Pos) const{
	Array<N>::index result;
	IdxFromPos(Pos,result);
	return result;
}
#endif