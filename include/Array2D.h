#ifndef TABLE2D__H
#define TABLE2D__H value

#include <cstdlib>

class Array2D
{
public:
	Array2D();
	~Array2D();
	void Init(size_t SizeX, size_t SizeY);
	void Clear();
	inline bool Ready() const{return (data!=0);}
	double Eval(double ix,double iy) const;
	
	inline size_t Len()   const {return sizeX*sizeY;}
	inline size_t SizeX() const {return sizeX;}
	inline size_t SizeY() const {return sizeY;}

	inline double& operator ()(size_t i,size_t j)      {return At(i,j);}
	inline double  operator ()(size_t i,size_t j) const{return At(i,j);}
private:
	double& At(size_t i, size_t j) const;
	size_t sizeX,sizeY;
	double * data;
};
#endif