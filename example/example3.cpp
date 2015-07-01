#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "RootUtils.h"
#include "Interpolator.h"
#include "MCSampler.h"
#include <fstream>
#include <functional>
#include "Timer.h"

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
        sprintf(fname,"%s/cz%02li.mflx",path,20-ny);
        ReadFileHonda(fname,aY(ny),result);
    }
    return result;
}


double PdfFromTable_N(const MCSampler<2>::Point &p,Table<2>* table){
    return table->Eval<Interpolation::Nearest>(p);
    // return table->Linear(p);
}

double PdfFromTable_L(const MCSampler<2>::Point &p,Table<2>* table){
    // return table->Eval<Interpolation::Nearest>(p);
    return table->Eval<Interpolation::Linear>(p);
}

int main(int argc, char const *argv[])
{   
    Timer timer1;
    using namespace std::placeholders;
    auto hondaFlux=ReadHonda(argv[1]);
    printf("=== Done ===\n");
    printf("Duration: %6.4g s\n",timer1.Update().count());
    // for(auto && idx: hondaFlux.GetArray().Dimensions()){
        // printf("[%d %d]=%g\n",idx[0],idx[1],hondaFlux.GetArray()(idx));
    // }
    TH2D h0=make_TH2D(hondaFlux,"hondaFlux; P_mu, GeV; cos#theta_{zenith}");
    TH2D h_1("hmc","mcFlux nearest; P_mu, GeV; cos#theta_{zenith}",200,hondaFlux.Min(0),hondaFlux.Max(0),200,hondaFlux.Min(1),hondaFlux.Max(1));
    TH2D h_2("hmc","mcFlux linear;  P_mu, GeV; cos#theta_{zenith}",200,hondaFlux.Min(0),hondaFlux.Max(0),200,hondaFlux.Min(1),hondaFlux.Max(1));

    ///---- generate 10000 MC points ----------
    const size_t Npoint=10000;
    double pmax=hondaFlux.MaxValue();

    MCSampler <2> sampler_n(std::bind(PdfFromTable_N, _1, &hondaFlux),{{0.0,0.0},{5.0,1.0}});
    printf("Nearest sampling:\n");
    timer1.Update();
    for(size_t n=0;n<Npoint;++n){
        if(n%(Npoint/100)==0){printf("."); fflush(stdout);}
        MCSampler<2>::Point r=sampler_n.GenPoint(pmax);
        h_1.Fill(r[0],r[1]);
    }
    printf("!\n");
    printf("Duration: %6.4g s\n",timer1.Update().count());  
    printf("eff=%g\n",sampler_n.Efficiency());
    MCSampler <2> sampler_l(std::bind(PdfFromTable_L, _1, &hondaFlux),{{0.0,0.0},{5.0,1.0}});
    printf("Linear sampling:\n");
    timer1.Update();
    for(size_t n=0;n<Npoint;++n){
        if(n%(Npoint/100)==0){printf("."); fflush(stdout);}
        MCSampler<2>::Point r=sampler_l.GenPoint(pmax);
        h_2.Fill(r[0],r[1]);
    }
    printf("!\n");
    printf("Duration: %6.4g s\n",timer1.Update().count());  
    printf("eff=%g\n",sampler_l.Efficiency());
    ///draw everything
    // TGraph gmc(Npoint,px,py);
    // gStyle->SetOptStat(0);
    gStyle->SetOptLogz(1);
    TCanvas* c=new TCanvas("c1","c1",2000,1000);
    c->Divide(2,2);
    c->cd(1); h0.Draw("colz ");// h0.SetMinimum(-2.0); h0.SetMaximum(2.0);
    c->cd(3); h_1.Draw("colz ");// h0.SetMinimum(-2.0); h0.SetMaximum(2.0);
    c->cd(4); h_2.Draw("colz ");// h0.SetMinimum(-2.0); h0.SetMaximum(2.0);
    // gmc.Draw("same p");
    TFile* fout=new TFile("hondaFlux.root","RECREATE");
    fout->cd();
    h0.Write("fluxTable");
    TGraph2D g0=make_TGraph2D(hondaFlux);
    g0.SetTitle("hondaFlux; P_mu, GeV; cos#theta_{zenith}");
    g0.Write("fluxGraph");
    fout->Close();
    c->Print("example3.png"); 
}