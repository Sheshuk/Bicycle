#include "Array1D.h"

Array1D::Array1D():sizeX(0),data(0){
}

Array1D::~Array1D(){
	Clear();
}

void Array1D::Init(unsigned SizeX){
	Clear();
	sizeX=SizeX;
	if(sizeX) data=new double[Len()];
}

void Array1D::Clear(){
	if(Ready())delete[] data;
	data=0;
}

double Array1D::Eval(double xi) const{
	int xi0=int(xi);
	double x=xi-xi0;
	if(xi0<0)xi0=0; if(xi0>sizeX-1)xi0=sizeX-1;
	double f0=At(xi0  );
	double f1=At(xi0+1);
	return f0+x*(f1-f0);
}