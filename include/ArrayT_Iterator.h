#ifndef ARRAYT_ITERATOR__H
#define ARRAYT_ITERATOR__H value

template<size_t N>
class Array<N>::iterator{
public:
	iterator(const Array<N> *A, size_t Pos):array(A),pos(Pos){};
	virtual ~iterator(){}
	bool operator!= (const Array<N>::iterator& other) const {return other.pos!=pos;}
	const Array<N>::iterator operator++(){++pos;return *this;}
	double& operator*() const{return array->data[pos];}
protected:
	/* data */
	const Array<N> *array;
	size_t pos;
};


// -------------------------------------------------
// template<size_t N>
// class Array<N>::Values{
// 	class iterator:public Array<N>::iterator{
// 	public:
// 		iterator(const Array& A,size_t Pos):Array<N>::iterator(A,Pos){};
// 		double& operator*() const{return array->data[pos];}
// 	};
// public:
// 	Values(Array<N>& A):array(A){};
// 	iterator begin() const{return iterator(array,0);}
// 	iterator end()   const{return iterator(array,array.length);}
// private:
// 	Array<N> &array;
// };
// template<size_t N> 

#endif