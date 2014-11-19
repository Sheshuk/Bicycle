#include "TCanvas.h"
#include "RootUtils.h"
int main(int argc, char const *argv[])
{	
	Axis ax0({50, 0,20});
	Table<1> table0({ax0});
	for(auto&& x : Axis::Values(ax0)){
		table0.SetPoint({x},cos(3.1415*0.02*x*x));
	}

	Axis ax1({1000,0,20});
	Table<1> table1({ax1});
	Table<1> table2({ax1});
	Table<1> table3({ax1});
	for(auto&& x : Axis::Values(ax1)) {
		printf("x=%4.2f\n",x);
		table1.SetPoint({x},table0.Nearest ({x}));
		table2.SetPoint({x},table0.Linear  ({x}));
		table3.SetPoint({x},table0.Lagrange({x}));
	}

	TGraph g0=make_TGraph(table0);
	g0.SetMarkerStyle(4);
	g0.SetMarkerColor(kBlack);
	TGraph g1=make_TGraph(table1);
	g1.SetMarkerStyle(6);
	g1.SetMarkerColor(kRed+2);
	g1.SetLineColor(kRed);
	TGraph g2=make_TGraph(table2);
	g2.SetMarkerStyle(6);
	g2.SetMarkerColor(kBlue+2);
	g2.SetLineColor(kBlue);
	TGraph g3=make_TGraph(table3);
	g3.SetMarkerStyle(7);
	g3.SetMarkerColor(kGreen+2);
	g3.SetLineColor(kGreen);
	TCanvas* c=new TCanvas;
	g0.Draw("AP");
	g1.Draw("same L");
	g2.Draw("same L");
	g3.Draw("same L");
	c->Print("example1.png");

}