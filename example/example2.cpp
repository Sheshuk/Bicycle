#include "TCanvas.h"
#include "TStyle.h"
#include "RootUtils.h"
#include "Timer.h"

int main(int argc, char const *argv[])
{	
	Axis ax0({20, 0,20});
	Axis ay0({20, 0,20});
	Table<2> table0({ax0,ay0});
	for(auto&& x : Axis::Values(ax0)){
		for(auto&& y : Axis::Values(ay0)){
			table0.SetPoint({x,y},cos(3.1415*0.01*x*x)+cos(3.1415*0.01*y*y));
		}
	}

	Axis ax1({200,0,20});
	Axis ay1({200,0,20});
	Table<2> table1({ax1,ay1});
	Table<2> table2({ax1,ay1});
	Table<2> table3({ax1,ay1});
	printf("Data table: [%d x %d]\n",table0.Nbins(0),table0.Nbins(1));
	printf("=== [1] NEAREST interpolation ===\n");
	
	Timer timer1;
	for(auto&& x : Axis::Values(ax1)){
		for(auto&& y : Axis::Values(ay1)){
			std::array<double,2> pnt={x,y};
			table1.SetPoint(pnt,table0.Nearest(pnt));
		}
	}

	printf("Duration: %6.4g s\n",timer1.Update().count());	
	printf("=== [2] LINEAR interpolation ===\n");
	for(auto&& x : Axis::Values(ax1)){
		for(auto&& y : Axis::Values(ay1)){
			std::array<double,2> pnt={x,y};
			table2.SetPoint(pnt,table0.Linear(pnt));
		}
	}

	printf("Duration: %6.4g s\n",timer1.Update().count());
	printf("=== [3] LAGRANGE interpolation ===\n");
	for(auto&& x : Axis::Values(ax1)){
		for(auto&& y : Axis::Values(ay1)){	
			std::array<double,2> pnt={x,y};
			table3.SetPoint(pnt,table0.Lagrange(pnt));
		}
	}

	printf("Duration: %6.4g s\n",timer1.Update().count());
	printf("=== Done ===\n");
	TH2D h0=make_TH2D(table0,"data");
	TH2D h1=make_TH2D(table1,"nearest");
	TH2D h2=make_TH2D(table2,"linear");
	TH2D h3=make_TH2D(table3,"lagrange");

	gStyle->SetOptStat(0);
	TCanvas* c=new TCanvas;
	c->Divide(2,2);
	c->cd(1);h0.Draw("colz"); h0.SetMinimum(-2.0); h0.SetMaximum(2.0);
	c->cd(2);h1.Draw("colz"); h1.SetMinimum(-2.0); h1.SetMaximum(2.0);
	c->cd(3);h2.Draw("colz"); h2.SetMinimum(-2.0); h2.SetMaximum(2.0);
	c->cd(4);h3.Draw("colz"); h3.SetMinimum(-2.0); h3.SetMaximum(2.0);
	c->Print("example2.png"); 

}