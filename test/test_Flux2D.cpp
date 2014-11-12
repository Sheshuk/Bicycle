#include "gtest/gtest.h"
#include "Axis.h"
#include "Table2D.h"
#include "TableReader.h"
#include <cmath>

TableReader reader;

double Constant(double x,double y){
	return 1.;
}

double Oscillating(double x,double y){
	return sin(x)+sin(y);
}

TEST(Test_Table2D,Table_From_Function){
	Table2D flux=reader.FromFunction(Axis(100,-10,10),Axis(100,-10,10),Constant);
	for (auto x: AxisValues(flux.GetXaxis()))
		for (auto y: AxisValues(flux.GetYaxis())){
			ASSERT_FLOAT_EQ(1.0,flux.At(x,y));
		}
	}


TEST(Test_Table2D,Table_vs_Table_Agreement){
	Table2D flux=reader.FromFunction(Axis(100,-10,10),Axis(100,-0,20),Oscillating);
	double x,y,zTable,zArray;
	for (unsigned nx: AxisBins(flux.GetXaxis()))
		for (unsigned ny: AxisBins(flux.GetYaxis())){
			zArray=flux.GetArray().At(nx,ny);
			x=flux.GetXaxis()(nx);
			y=flux.GetYaxis()(ny);
			zTable =flux.At(x,y);
			ASSERT_NEAR(zArray,zTable,1e-10);
		}
	}

