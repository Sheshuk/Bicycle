#include "TCanvas.h"
#include "TMultiGraph.h"
#include "RootUtils.h"
#include "Interpolator.h"
int main(int argc, char const *argv[])
{	
	Axis ax0({20, 0,20});
	Table<1> table0({ax0});
	for(auto&& x : Axis::Values(ax0)){
		table0.SetPoint({x},cos(3.1415*0.02*x*x));
	}

	Axis ax1({1000,0,20});
	Table<1> tableNrs({ax1});
	Table<1> tableLin({ax1});
	Table<1> tableLag({ax1});
	Table<1> tableIDW({ax1});
	for(auto&& x : Axis::Values(ax1)) {
		tableNrs.SetPoint({x},table0.Eval<Interpolation::Nearest >({x}));
		tableLin.SetPoint({x},table0.Eval<Interpolation::Linear  >({x}));
		tableLag.SetPoint({x},table0.Eval<Interpolation::Lagrange>({x}));
		tableIDW.SetPoint({x},table0.Eval<Interpolation::IDW     >({x}));
	}

	TGraph g0=make_TGraph(table0);
	g0.SetMarkerStyle(4);
	g0.SetMarkerColor(kBlack);
	TGraph g1=make_TGraph(tableNrs);
	g1.SetMarkerStyle(6);
	g1.SetMarkerColor(kRed+2);
	g1.SetLineColor(kRed);
	TGraph g2=make_TGraph(tableLin);
	g2.SetMarkerStyle(6);
	g2.SetMarkerColor(kBlue+2);
	g2.SetLineColor(kBlue);
	TGraph g3=make_TGraph(tableLag);
	g3.SetMarkerStyle(7);
	g3.SetMarkerColor(kGreen+2);
	g3.SetLineColor(kGreen+2);
	TGraph g4=make_TGraph(tableIDW);
	g4.SetMarkerStyle(7);
	g4.SetMarkerColor(kGreen);
	g4.SetLineColor(kGreen);
	TCanvas* c=new TCanvas;
	TMultiGraph mg;
	mg.Add(&g0);
	mg.Add(&g1);
	mg.Add(&g2);
	mg.Add(&g3);
	mg.Add(&g4);
	mg.SetMaximum(5);
	mg.SetMinimum(-5);
	mg.Draw("AL");
	c->Print("example1.png");

}