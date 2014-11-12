#ifndef FLUXREADER__H
#define FLUXREADER__H value

class Axis;
class Table1D;
class Table2D;

class TableReader
{
public:
	static Table2D Honda(const char* path);
	static Table2D FromFunction(Axis ax,Axis ay,double(*fun)(double, double));
	static Table1D FromFunction(Axis ax, double(*fun)(double));
private:
	static void ReadFileHonda(const char* fname, unsigned ny,Table2D& table);
};
#endif