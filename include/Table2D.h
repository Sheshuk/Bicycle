#ifndef FLUX2D__H
#define FLUX2D__H value
#include "Axis.h"
#include "Array2D.h"

class Table2D
{
public:
	Table2D(Axis XAxis, Axis YAxis);
	~Table2D(){};
	double At (double x, double y) const;
	inline unsigned NBinsX() const{return axisX.Nbins();}
	inline unsigned NBinsY() const{return axisY.Nbins();}
	inline double  Xmin() const {return axisX.Min();}
	inline double  Xmax() const {return axisX.Max();}
	inline double  Ymin() const {return axisY.Min();}
	inline double  Ymax() const {return axisY.Max();}

	const Axis& GetXaxis() const{return axisX;}
	const Axis& GetYaxis() const{return axisY;}

	const Array2D& GetArray() const{return array;}
	Array2D& GetArray() {return array;}
	
	void SetPoint(unsigned nx,unsigned ny, double Val){array.At(nx,ny)=Val;}
private:	
	Axis axisX,axisY;
	Array2D array;
};
#endif