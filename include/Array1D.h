#ifndef TABLE1D__H
#define TABLE1D__H value
class Array1D
{
public:
	Array1D();
	~Array1D();
	void Init(unsigned SizeX);
	void Clear();
	inline bool Ready() const{return (data!=0);}
	double Eval(double ix) const;
	
	inline unsigned Len()   const {return sizeX;}
	inline unsigned SizeX() const {return sizeX;}

	inline double& operator ()(unsigned i)      {return At(i);}
	inline double  operator ()(unsigned i) const{return At(i);}

private:
	double& At(unsigned i) const;
	unsigned sizeX;
	double * data;
};
#endif