
#include "RootUtils.h"
#include "Interpolator.h"
Axis make_Axis(const TAxis& a){return Axis(a.GetNbins(),a.GetXmin(),a.GetXmax());}

TGraph   make_TGraph(const Table<1>& table){
	TGraph graf(table.Nbins(0));
	graf.SetName("1dim graph");
	unsigned n=0;
	for (auto x:Axis::Values(table.GetAxis(0))){
		graf.SetPoint(n++,x,table.Eval<Interpolation::Nearest>({x}));
	}
	return graf;
};

TGraph2D make_TGraph2D(const Table<2>& flux){
	TGraph2D graf(flux.Nbins(0)*flux.Nbins(1));
	graf.SetName("2dim graph");
	unsigned n=0;
	for (auto x:Axis::Values(flux.GetAxis(0))){
		for (auto y:Axis::Values(flux.GetAxis(1))){
			graf.SetPoint(n++,x,y,flux.Eval<Interpolation::Nearest>({x,y}));
		}
	}
	return graf;
};

TH1D     make_TH1D(const Table<1> &flux, const char* title){
	const Axis &ax=flux.GetAxis(0);
	TH1D hist("h1d",title,ax.Nbins(),ax.Min(),ax.Max());
	for(auto nx:Axis::Bins(ax))
			hist.SetBinContent(nx+1,flux.Eval<Interpolation::Nearest>({ax(nx)}));
	return hist;
};
TH2D     make_TH2D(const Table<2> &flux, const char* title){
	const Axis &ax=flux.GetAxis(0);
	const Axis &ay=flux.GetAxis(1);
	TH2D hist("h2d",title,ax.Nbins(),ax.Min(),ax.Max(),ay.Nbins(),ay.Min(),ay.Max());
	for(auto nx:Axis::Bins(ax))
		for(auto ny:Axis::Bins(ay)){
			hist.SetBinContent(nx+1,ny+1,flux.Eval<Interpolation::Nearest>({ax(nx),ay(ny)}));
		}
	return hist;
}

TH3D     make_TH3D(const Table<3> &flux, const char* title){
	const Axis &ax=flux.GetAxis(0);
	const Axis &ay=flux.GetAxis(1);
	const Axis &az=flux.GetAxis(2);
	TH3D hist("h2d",title,ax.Nbins(),ax.Min(),ax.Max(),ay.Nbins(),ay.Min(),ay.Max(),az.Nbins(),az.Min(),az.Max());
	for(auto nx:Axis::Bins(ax))
		for(auto ny:Axis::Bins(ay))
			for(auto nz:Axis::Bins(az)){
				hist.SetBinContent(nx+1,ny+1,nz+1,flux.Eval<Interpolation::Nearest>({ax(nx),ay(ny),az(nz)}));
			}
	return hist;
}

Table<1> make_Table1D(const TH1D& hist){
	Axis ax=make_Axis(*hist.GetXaxis());
	Table<1> result=Table<1>({ax});
	for(auto nx:Axis::Bins(ax))
		{
			auto val=hist.GetBinContent(nx+1);
			result.SetPoint({ax(nx)},val);
		}
	return result;	
}

Table<2> make_Table2D(const TH2D& hist){
	Axis ax=make_Axis(*hist.GetXaxis());
	Axis ay=make_Axis(*hist.GetYaxis());
	Table<2> result=Table<2>({ax,ay});
	for(auto nx:Axis::Bins(ax))
		for(auto ny:Axis::Bins(ay)){
			auto val=hist.GetBinContent(nx+1,ny+1);
			result.SetPoint({ax(nx),ay(ny)},val);
		}
	return result;	
}

Table<3> make_Table3D(const TH3D& hist){
	Axis ax=make_Axis(*hist.GetXaxis());
	Axis ay=make_Axis(*hist.GetYaxis());
	Axis az=make_Axis(*hist.GetZaxis());
	Table<3> result=Table<3>({ax,ay,az});
	for(auto nx:Axis::Bins(ax))
		for(auto ny:Axis::Bins(ay))
			for(auto nz:Axis::Bins(az)){
				auto val=hist.GetBinContent(nx+1,ny+1,nz+1);
				result.SetPoint({ax(nx),ay(ny),az(nz)},val);
			}
	return result;	
}
