#include "TCanvas.h"
#include "TStyle.h"
#include "RootUtils.h"
#include <fstream>

void ReadFileHonda(const char* fname, double cz,Table<2>& table){
    // printf("reading file %s (for Y[%d])\n",fname,ny);
    std::ifstream inf;
    inf.open(fname);
    if(!inf.good()) throw MRexception("Error opening file: \""+std::string(fname)+"\"");
    double p,mplus,mminus;
    do {
        inf>>p>>mplus>>mminus;
        if(inf.eof())break;
        if(inf.fail()){
            throw MRexception("Failed reading from file");
        }
        printf("flux[%f, %f]=%g\n",p,cz,mplus+mminus);
        table.SetPoint({log10(p),cz},mplus+mminus);
    } while(!inf.eof());
    inf.close();
}

Table<2> ReadHonda(const char* path){
    Axis aX(101,0.0,5.0);
    Axis aY(20,0.025,0.975);
    Table<2> result({aX,aY});
    
    char fname[100];
    for(auto ny:Axis::Bins(aY)){
        sprintf(fname,"%s/cz%02li.mflx",path,ny+1);
        ReadFileHonda(fname,aY(ny),result);
    }
    return result;
}

typename Table<2>::point GenPoint(Table<2>);

int main(int argc, char const *argv[])
{   
    auto hondaFlux=ReadHonda(argv[1]);
    printf("=== Done ===\n");
    for(auto && idx: hondaFlux.GetArray().Dimensions()){
        printf("[%d %d]=%g\n",idx[0],idx[1],hondaFlux.GetArray()(idx));
    }
    TH2D h0=make_TH2D(hondaFlux,"hondaFlux; P_mu, GeV; cos#theta_{zenith}");
    gStyle->SetOptStat(0);
    TCanvas* c=new TCanvas("c1","c1",2000,400);
    h0.Draw("colz text");// h0.SetMinimum(-2.0); h0.SetMaximum(2.0);
    c->Print("example3.png"); 

}