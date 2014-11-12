#ifndef FLUX1D__H
#define FLUX1D__H value
#include "Axis.h"
#include "Array1D.h"

class Table1D
{
public:
	Table1D(Axis XAxis);
	~Table1D(){};
	double At (double x) const;
	inline unsigned NBinsX() const{return axisX.Nbins();}
	inline double  Xmin() const {return axisX.Min();}
	inline double  Xmax() const {return axisX.Max();}

	const Axis& GetXaxis() const{return axisX;}

	const Array1D& GetArray() const{return array;}
	      Array1D& GetArray()      {return array;}
	      
	void SetPoint(unsigned nx, double Val){array(nx)=Val;}
private:	
	Axis axisX;
	Array1D array;
};
#endif