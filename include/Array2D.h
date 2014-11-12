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
	inline double& At(unsigned i, unsigned j) const{return data[j*sizeX+i];}
	
	inline unsigned Len()   const {return sizeX*sizeY;}
	inline unsigned SizeX() const {return sizeX;}
	inline unsigned SizeY() const {return sizeY;}
private:
	unsigned sizeX,sizeY;
	double * data;
};
#endif