#include "TableIntegrator.h"
#include "Table2D.h"
#include "Table1D.h"
#include "TF1.h"

double __arg(double x){return x;}

const Table2D* __flu=0;
double (* __argFun)(double)=__arg;

double __integrandX(double* arg, double * par){
	return __flu->At(__argFun(arg[0]),par[0]);
}

double __integrandY(double* arg, double * par){
	return __flu->At(par[0],__argFun(arg[0]));
}


Integral::Integral(const Table2D &Table)
:flux(Table)
{}

Table1D Integral::dX   (double x0, double x1,double (*ArgFun)(double)){
	__argFun=ArgFun?(ArgFun):__arg;
	__flu=&flux;
	// if(x0<flux.GetXaxis().Min())x0=flux.GetXaxis().Min();
	// if(x1>flux.GetXaxis().Max())x1=flux.GetXaxis().Max();
	printf("Integral over dX in limits [%6.4g<X<%6.4g] --> in table [%6.4g<X<%6.4g]\n",x0,x1,__argFun(x0),__argFun(x1));
	TF1 rootFunc("integrand",__integrandX,x0,x1,1);

	Axis otherAxis=flux.GetYaxis();
	Table1D result(otherAxis);

	for(unsigned n : Axis::Bins(otherAxis)) {
		rootFunc.SetParameter(0,otherAxis(n));
		double J=rootFunc.Integral(x0,x1);
		result.SetPoint(n,J);
	}
	return result;
};