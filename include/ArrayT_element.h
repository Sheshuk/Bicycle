#ifndef ARRAYT_ELEMENT__H
#define ARRAYT_ELEMENT__H value
template<size_t N>
class Array<N>::element{
public:
	element(Array<N>& A,size_t Pos):value(A.data[Pos]),idx(A.Index(Pos)){};
	double& value;
	typename Array<N>::index idx;
};
#endif