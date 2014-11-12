#include <cmath>
#include "Array2D.h"

Array2D::Array2D():sizeX(0),sizeY(0),data(0){
}

Array2D::~Array2D(){
	Clear();
}

void Array2D::Init(unsigned SizeX, unsigned SizeY){
	Clear();
	sizeX=SizeX;
	sizeY=SizeY;
	if(sizeX&&sizeY) data=new double[Len()];
}

void Array2D::Clear(){
	if(Ready())delete[] data;
	data=0;
}

double Array2D::Eval(double xi,double yi) const{
	int xi0=floor(xi);
	int yi0=floor(yi);
	if(xi0<0)xi0=0; if(xi0>sizeX-2)xi0=sizeX-2;
	if(yi0<0)yi0=0; if(yi0>sizeY-2)yi0=sizeY-2;
	double x=xi-xi0;
	double y=yi-yi0;
	double f00=At(xi0,  yi0  );
	double f01=At(xi0,  yi0+1);
	double f10=At(xi0+1,yi0  );
	double f11=At(xi0+1,yi0+1);
	return f00+x*(f10-f00)+y*(f01-f00)+x*y*(f00-f01-f10+f11);
}