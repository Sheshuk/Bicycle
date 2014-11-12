#include "Axis_Iterator.h"
#include "Table2D.h"


Table2D::Table2D(Axis XAxis, Axis YAxis):axisX(XAxis),axisY(YAxis){
	array.Init(NBinsX(),NBinsY());
};

double Table2D::At(double x, double y) const{
    double ix=axisX.IdxFromVal(x);
    double iy=axisY.IdxFromVal(y);
	// if(!axisX.isInRange(x)||!axisY.isInRange(y))return 0;
	return array.Eval(ix,iy);
};

