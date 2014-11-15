#include <cmath>
#include "gtest/gtest.h"
#include "Table1D.h"
#include "Table2D.h"
#include "TableIntegrator.h"
#include "TableFactory.h"

TEST (test_TableIntegrator, Integrate_dX_const){
	Table2D my_table_2d=TableFactory::FromFunction(
		Axis(10,-50,50),Axis(10,-50,50),
		[](double x, double y)->double {return 1.0;}
		);

	Table1D my_table_1d_20=Integral(my_table_2d).dX(-10,10);
	for(auto&& y : Axis::Values(my_table_2d.GetYaxis())) {
		ASSERT_DOUBLE_EQ(20,my_table_1d_20.At(y));
	}

	Table1D my_table_1d_2=Integral(my_table_2d).dX(0,2);
	for(auto&& y : Axis::Values(my_table_1d_2.GetXaxis())) {
		EXPECT_DOUBLE_EQ(2,my_table_1d_2.At(y));
	}
}

TEST (test_TableIntegrator, Integrate_dX_sin){
	Table2D my_table_2d=TableFactory::FromFunction(
		Axis(1000,-5,5),Axis(10,-50,50),
		[](double x,double y)->double {return sin(x)*sin(y);}
		);
	Table1D my_table_1d_sim=Integral(my_table_2d).dX(-1,1);
	for(auto&& y : Axis::Values(my_table_2d.GetYaxis())) {
		ASSERT_NEAR(0,my_table_1d_sim.At(y),1e-10);
	}

	Table1D my_table_1d_asim=Integral(my_table_2d).dX(0,3.1415);
	for(auto&& y : Axis::Values(my_table_1d_asim.GetXaxis())) {
		ASSERT_NEAR(2*sin(y),my_table_1d_asim.At(y), 1e-4);
	}
}

TEST (test_TableIntegrator, Integrate_dX_log){
	Table2D my_table_2d=TableFactory::FromFunction(
		Axis(100,0,20),Axis(10,-50,50),
		[](double x,double y)->double {return exp(-x);}
		);
	Table1D my_table_1d_20=Integral(my_table_2d).dX(1,2.718281828,log);
	for(auto&& y : Axis::Values(my_table_2d.GetYaxis())) {
		ASSERT_NEAR(1.0,my_table_1d_20.At(y),1e-2);
	}
}