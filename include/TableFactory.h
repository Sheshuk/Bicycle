#ifndef FLUXREADER__H
#define FLUXREADER__H value

#include <functional>
class Axis;
class Table1D;
class Table2D;
class TableFactory
{
public:
	static Table2D Honda(const char* path);
	static Table2D FromFunction(Axis ax,Axis ay,std::function<double(double, double)> fun);
	static Table1D FromFunction(Axis ax, std::function<double(double)> fun);
private:
	static void ReadFileHonda(const char* fname, unsigned ny,Table2D& table);
};
#endif