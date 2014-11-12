#include "gtest/gtest.h"
#include "Axis.h"

TEST (TestAxis, ConstructionParameters){
	Axis a(10,-1,2);
	EXPECT_EQ(a.Nbins(),10);
	EXPECT_DOUBLE_EQ(a.Min(),-1);
	EXPECT_DOUBLE_EQ(a.Max(), 2);
}

TEST (TestAxis, IsInRange_Positive){
	Axis a(10,-5,10);
	EXPECT_TRUE(a.isInRange( 7));
	EXPECT_TRUE(a.isInRange(-5));
	EXPECT_TRUE(a.isInRange(10));
	
	EXPECT_FALSE(a.isInRange(-6));
	EXPECT_FALSE(a.isInRange(100));
}

TEST (TestAxis, IsInRange_Negative){
	Axis a(20,0.975,0.025);
	EXPECT_TRUE(a.isInRange(0.5  ));
	EXPECT_TRUE(a.isInRange(0.975));
	EXPECT_TRUE(a.isInRange(0.025));
	
	EXPECT_FALSE(a.isInRange(-6));
	EXPECT_FALSE(a.isInRange(100));
}

TEST (TestAxis, ValFromIdx_Positive){
	Axis a(201,-100,100);
	EXPECT_DOUBLE_EQ(a.ValFromIdx(0)  ,-100);
	EXPECT_DOUBLE_EQ(a.ValFromIdx(0.5),-99.5);
	EXPECT_DOUBLE_EQ(a.ValFromIdx(200), 100);
	EXPECT_DOUBLE_EQ(a.ValFromIdx(100),   0);
}
TEST (TestAxis, ValFromIdx_Negative){
	Axis a(201,100,-100);
	EXPECT_DOUBLE_EQ(a.ValFromIdx(0)  , 100);
	EXPECT_DOUBLE_EQ(a.ValFromIdx(0.5),99.5);
	EXPECT_DOUBLE_EQ(a.ValFromIdx(200),-100);
	EXPECT_DOUBLE_EQ(a.ValFromIdx(100),   0);
}
TEST (TestAxis, IdxFromVal_Positive){
	Axis a(201,-100,100);
	EXPECT_DOUBLE_EQ(a.IdxFromVal(-100)    ,0);
	EXPECT_DOUBLE_EQ(a.IdxFromVal(99.5),199.5);
	EXPECT_DOUBLE_EQ(a.IdxFromVal(0),     100);
	EXPECT_DOUBLE_EQ(a.IdxFromVal(100),   200);
}
TEST (TestAxis, IdxFromVal_Negative){
	Axis a(201, 100,-100);
	EXPECT_DOUBLE_EQ(a.IdxFromVal( 100)     ,0);
	EXPECT_DOUBLE_EQ(a.IdxFromVal(-99.5),199.5);
	EXPECT_DOUBLE_EQ(a.IdxFromVal( 0),     100);
	EXPECT_DOUBLE_EQ(a.IdxFromVal(-100),   200);
}

TEST (TestAxis, Reversibility_Index_Value){
	Axis a(201,-100,100);
	EXPECT_FLOAT_EQ(a.ValFromIdx(a.IdxFromVal(12.3456)),12.3456);
	EXPECT_FLOAT_EQ(a.ValFromIdx(a.IdxFromVal(-100)),-100);
	EXPECT_FLOAT_EQ(a.ValFromIdx(a.IdxFromVal( 100)), 100);
	EXPECT_FLOAT_EQ(a.IdxFromVal(a.ValFromIdx(123.456)),123.456);
	EXPECT_FLOAT_EQ(a.IdxFromVal(a.ValFromIdx(0)),0);
	EXPECT_FLOAT_EQ(a.IdxFromVal(a.ValFromIdx(200)),200);
}