
#include "RootUtils.h"

TGraph   make_TGraph(const Table<1>& table){
	TGraph graf(table.Nbins(0));
	graf.SetName("1dim graph");
	unsigned n=0;
	for (auto x:Axis::Values(table.GetAxis(0))){
		graf.SetPoint(n++,x,table.At({x}));
	}
	return graf;
};

TGraph2D make_TGraph2D(const Table<2>& flux){
	TGraph2D graf(flux.Nbins(0)*flux.Nbins(1));
	graf.SetName("2dim graph");
	unsigned n=0;
	for (auto x:Axis::Values(flux.GetAxis(0))){
		for (auto y:Axis::Values(flux.GetAxis(1))){
			graf.SetPoint(n++,x,y,flux.At({x,y}));
		}
	}
	return graf;
};

TH1D     make_TH1D(const Table<1> &flux, const char* title){
	const Axis &ax=flux.GetAxis(0);
	TH1D hist("h1d",title,ax.Nbins(),ax.Min(),ax.Max());
	for(auto nx:Axis::Bins(ax))
			hist.SetBinContent(nx+1,flux.At({ax(nx)}));
	return hist;
};
TH2D     make_TH2D(const Table<2> &flux, const char* title){
	const Axis &ax=flux.GetAxis(0);
	const Axis &ay=flux.GetAxis(1);
	TH2D hist("h2d",title,ax.Nbins(),ax.Min(),ax.Max(),ay.Nbins(),ay.Min(),ay.Max());
	for(auto nx:Axis::Bins(ax))
		for(auto ny:Axis::Bins(ay)){
			hist.SetBinContent(nx+1,ny+1,flux.At({ax(nx),ay(ny)}));
		}
	return hist;
}