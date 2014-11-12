#ifndef FLUXINTEGRATOR__H
#define FLUXINTEGRATOR__H value
class Table1D;
class Table2D;

class Integral
{
public:
	Integral(const Table2D &Table);
	Table1D dX   (double x0=0, double x1=1,double (* ArgFun)(double)=0);

private:
	const Table2D& flux;
};
#endif