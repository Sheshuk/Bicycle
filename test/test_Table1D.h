#include "gtest/gtest.h"
#include "Axis.h"
#include "Table1D.h"
#include "TableReader.h"

double linear(double x){
	return 0.5*x;
}

double foo(double x){
	return x*x*x+2*x*x-3*x+12.5;
}

TEST(Test_Table1D,Create_FromFunction){
	Table1D subject=TableReader::FromFunction(Axis(100,-10,10),foo);
	for (auto x: AxisValues(subject.GetXaxis())){
		ASSERT_NEAR(foo(x),subject.At(x),1e-12);
	}
}

TEST(Test_Table1D,Interpolation){
	Table1D subject=TableReader::FromFunction(Axis(20,-10,10),linear);
	for (auto x: AxisValues(Axis(100,-10,10))){
		ASSERT_NEAR(linear(x),subject.At(x),1e-12);
	}
}

TEST(Test_Table1D,Extrapolation){
	Table1D subject=TableReader::FromFunction(Axis(20,-10,10),linear);
	for (auto x: AxisValues(Axis(20,-30,-10))){
		EXPECT_NEAR(linear(x),subject.At(x),1e-12);
	}
}