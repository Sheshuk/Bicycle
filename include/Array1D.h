#ifndef TABLE1D__H
#define TABLE1D__H value

#include <cstdlib>

class Array1D
{
public:
	Array1D();
	~Array1D();
	void Init(size_t SizeX);
	void Clear();
	inline bool Ready() const{return (data!=0);}
	double Eval(double ix) const;
	
	inline size_t Len()   const {return sizeX;}
	inline size_t SizeX() const {return sizeX;}

	inline double& operator ()(size_t i)      {return At(i);}
	inline double  operator ()(size_t i) const{return At(i);}

private:
	double& At(size_t i) const;
	size_t sizeX;
	double * data;
};
#endif