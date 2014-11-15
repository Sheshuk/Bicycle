#include <cmath>
#include "MRexception.h"
#include "Array1D.h"

Array1D::Array1D():sizeX(0),data(0){
}

Array1D::~Array1D(){
	Clear();
}

double& Array1D::At(size_t i) const {
	if(i>sizeX-1)
		throw MRexception(
			std::string("Error acessing data with nx=")+
			std::to_string(i)+">"+std::to_string(sizeX-1)
			);
	return data[i];
};

void Array1D::Init(size_t SizeX){
	Clear();
	sizeX=SizeX;
	if(sizeX) data=new double[Len()];
}

void Array1D::Clear(){
	if(Ready())delete[] data;
	data=0;
}

double Array1D::Eval(double xi) const{
	int xi0=floor(xi);
	if(xi0<0)xi0=0; if(xi0>int(sizeX)-2)xi0=sizeX-2;
	double x=xi-xi0;
	double f0=At(xi0  );
	double f1=At(xi0+1);
	return f0+x*(f1-f0);
}