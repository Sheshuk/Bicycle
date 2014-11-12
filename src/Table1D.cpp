#include "Axis_Iterator.h"
#include "Table1D.h"


Table1D::Table1D(Axis XAxis):axisX(XAxis){
	array.Init(NBinsX());
};

double Table1D::At(double x) const{
    double ix=axisX.IdxFromVal(x);
	// if(!axisX.isInRange(x)||!axisY.isInRange(y))return 0;
	return array.Eval(ix);
};
