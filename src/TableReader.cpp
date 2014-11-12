#include <cstdio>
#include <fstream>
#include <string>

#include "Axis.h"
#include "Axis_Iterator.h"
#include "Table1D.h"
#include "Table2D.h"
#include "Array2D.h"

#include "MRexception.h"
#include "TableReader.h"

Table2D TableReader::Honda(){
    Axis aX(101,0.0,5.0);
    Axis aY(20,0.975,0.025);
    Table2D result(aX,aY);
    
    char fname[100];
    for(auto ny:AxisBins(aY)){
        sprintf(fname,"cz%02i.mflx",ny+1);
        ReadFileHonda(fname,ny,result);
    }
    return result;
}

void TableReader::ReadFileHonda(const char* fname, unsigned ny,Table2D& table){
    // printf("reading file %s (for Y[%d])\n",fname,ny);
    std::ifstream inf;
    inf.open(fname);
    if(!inf.good()) throw MRexception("Error opening file: \""+std::string(fname)+"\"");
    double p,mplus,mminus;
    for (auto nx:AxisBins(table.GetXaxis()))
    {
        inf>>p>>mplus>>mminus;
        if(inf.fail()){
            throw MRexception("Failed reading from file");
        }
        table.SetPoint(nx,ny,mplus+mminus);
    }
    inf.close();
}

Table2D TableReader::FromFunction(Axis ax,Axis ay,double(*fun)(double, double)){
    Table2D result(ax,ay);
    for(auto nx:AxisBins(ax)){
        for(auto ny:AxisBins(ay)){
            result.SetPoint(nx,ny,fun(ax(nx),ay(ny)));
        }
    }
    return result;
};

Table1D TableReader::FromFunction(Axis ax, double(*fun)(double)){
    Table1D result(ax);
    for(auto nx:AxisBins(ax)){
        result.SetPoint(nx,fun(ax(nx)));
    }
    return result;
}