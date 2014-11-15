#include <cstdio>
#include <fstream>
#include <string>

#include "Axis.h"
#include "Axis_Iterator.h"
#include "Table1D.h"
#include "Table2D.h"
#include "Array2D.h"

#include "MRexception.h"
#include "TableFactory.h"

Table2D TableFactory::Honda(const char* path){
    Axis aX(101,0.0,5.0);
    Axis aY(20,0.975,0.025);
    Table2D result(aX,aY);
    
    char fname[100];
    for(auto ny:Axis::Bins(aY)){
        sprintf(fname,"%s/cz%02i.mflx",path,ny+1);
        ReadFileHonda(fname,ny,result);
    }
    return result;
}

void TableFactory::ReadFileHonda(const char* fname, unsigned ny,Table2D& table){
    // printf("reading file %s (for Y[%d])\n",fname,ny);
    std::ifstream inf;
    inf.open(fname);
    if(!inf.good()) throw MRexception("Error opening file: \""+std::string(fname)+"\"");
    double p,mplus,mminus;
    for (auto nx:Axis::Bins(table.GetXaxis()))
    {
        inf>>p>>mplus>>mminus;
        if(inf.fail()){
            throw MRexception("Failed reading from file");
        }
        table.SetPoint(nx,ny,mplus+mminus);
    }
    inf.close();
}

Table2D TableFactory::FromFunction(Axis ax,Axis ay,std::function<double(double, double)> fun){
    Table2D result(ax,ay);
    for(auto nx:Axis::Bins(ax)){
        for(auto ny:Axis::Bins(ay)){
            result.SetPoint(nx,ny,fun(ax(nx),ay(ny)));
        }
    }
    return result;
};

Table1D TableFactory::FromFunction(Axis ax, std::function<double(double)> fun){
    Table1D result(ax);
    for(auto nx:Axis::Bins(ax)){
        result.SetPoint(nx,fun(ax(nx)));
    }
    return result;
}