#include <iostream>

#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH2D.h"
#include "TF2.h"
#include "TFile.h"
#include "TMath.h"

#include "Table2D.h"
#include "Table1D.h"
#include "MRexception.h"
#include "TableReader.h"
#include "TableIntegrator.h"

TGraph2D* GeneratePoints(const Table2D& flux, int Npoints){
	TGraph2D* graf=new TGraph2D(Npoints);
	graf->SetName("Points");
	double x,y,z;
	for (int i = 0; i < Npoints; ++i){
			x=gRandom->Uniform(flux.GetXaxis().Min(),flux.GetXaxis().Max());
			y=gRandom->Uniform(flux.GetYaxis().Min(),flux.GetYaxis().Max());
			z=flux.At(x,y);
			graf->SetPoint(i,x,y,z);
		}
	graf->SetMarkerStyle(7);
	return graf;
}

TGraph2D* MakeGridTable(const Table2D& flux){
	TGraph2D* graf=new TGraph2D(flux.NBinsX()*flux.NBinsY());
	graf->SetName("GridTable");
	double z;
	unsigned np=0;
	for (auto x:AxisValues(flux.GetXaxis()))
		for (auto y:AxisValues(flux.GetYaxis())){
			z=flux.At(x,y);
			graf->SetPoint(np++,x,y,z);
		}
	return graf;
}
TGraph* MakeGraph(const Table1D& flux){
	TGraph* graf=new TGraph(flux.NBinsX());
	graf->SetName("1dim graph");
	unsigned nx=0;
	for (auto x:AxisValues(flux.GetXaxis())){
		graf->SetPoint(nx++,x,flux.At(x));
	}
	return graf;
}

TGraph2D* MakeGridArray(const Table2D& flux){
	TGraph2D* graf=new TGraph2D(flux.NBinsX()*flux.NBinsY());
	graf->SetName("GridArray");
	double x,y,z;
	for (auto nx:AxisBins(flux.GetXaxis()))
		for (auto ny:AxisBins(flux.GetYaxis())){
			x=flux.GetXaxis()(nx);
			y=flux.GetYaxis()(ny);
			z=flux.GetArray().At(nx,ny);
			graf->SetPoint(nx*flux.NBinsY()+ny,x,y,z);
		}
	return graf;
}

const Table2D* TableForFun=0;
double Func(double* arg, double * par){
	return TableForFun->At(TMath::Log10(arg[0]),par[0]);
}

void Print(const Table1D& f){
	for(auto&& cz : AxisValues(f.GetXaxis())) {
		double J=f.At(cz);
		printf("i: === for cz=%2.4f J=%g\n",cz,J);
	}
}

Table2D Make_TXTY_Projection(const Table1D &dF_dCosZ){
	Axis aTX(201,-1.0,1.0);
	Axis aTY(201,-1.0,1.0);
	aTX.Print();
	Table2D result(aTX,aTY);
	double dTX=aTX.BinSize();
	double dTY=aTY.BinSize();
	for(auto nx:AxisBins(aTX))
		for(auto ny:AxisBins(aTY)){
			double tx=aTX(nx); double ty=aTY(ny);
			double A=sqrt(1+tx*tx+ty*ty);
			double Cz=TMath::Abs(ty/A);
			double W=dTX*dTY/(A*A*A);
			result.SetPoint(nx,ny,dF_dCosZ.At(Cz)*W);
		}
	return result;
}

double exposition=86400*154.0;
double surface=0.76;

TH2D* MakeTH2D(const Table2D &flux){
	const Axis &ax=flux.GetXaxis();
	const Axis &ay=flux.GetYaxis();
	TH2D* hist=new TH2D("fluxHist","fluxHist",ax.Nbins()-1,ax.Min(),ax.Max(),ay.Nbins()-1,ay.Min(),ay.Max());
	for(auto nx:AxisBins(ax))
		for(auto ny:AxisBins(ay)){
			hist->SetBinContent(nx,ny,flux.At(ax(nx),ay(ny)));
		}
	hist->Scale(exposition*surface);
	return hist;
}

int main(int argc, char const *argv[])
{
	gStyle->SetOptStat(0);
	try {
		TableReader reader;
		Table2D flux=reader.Honda();
		printf("Flux [%d x %d]\n",flux.NBinsX(),flux.NBinsY());
		TFile f("fluxPlots.root","RECREATE");
		MakeGridArray(flux);
		MakeGridTable (flux);
		GeneratePoints(flux,200);

		double low=atof(argv[1]);
		double high=atof(argv[2]);
		
		Table1D fluxCZ=Integral(flux).dX(low, high, TMath::Log10);
		for(auto&& deg : AxisValues(Axis(41,0,40))) {
			printf("Flux(%4.1f deg)=%g\n",deg,fluxCZ.At(cos(TMath::DegToRad()*(90-deg))));
		}
		MakeGraph(fluxCZ)->Write("Flux1d_CosZ");
		Table2D fluxTXTY=Make_TXTY_Projection(fluxCZ);

		TCanvas* c=new TCanvas;
		MakeTH2D(fluxTXTY)->Draw("colz");
		c->Print("FluxTXTY.png");
		f.Write();
		f.Close();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	return 0;
}