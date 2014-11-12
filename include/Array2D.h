#ifndef TABLE2D__H
#define TABLE2D__H value
class Array2D
{
public:
	Array2D();
	~Array2D();
	void Init(unsigned SizeX, unsigned SizeY);
	void Clear();
	inline bool Ready() const{return (data!=0);}
	double Eval(double ix,double iy) const;
	
	inline unsigned Len()   const {return sizeX*sizeY;}
	inline unsigned SizeX() const {return sizeX;}
	inline unsigned SizeY() const {return sizeY;}

	inline double& operator ()(unsigned i,unsigned j)      {return At(i,j);}
	inline double  operator ()(unsigned i,unsigned j) const{return At(i,j);}
private:
	double& At(unsigned i, unsigned j) const;
	unsigned sizeX,sizeY;
	double * data;
};
#endif