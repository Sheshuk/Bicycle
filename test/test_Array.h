#include "gtest/gtest.h"
#include "ArrayT.h"
#include "MRexception.h"

TEST (test_Array, Length){
	Array<1> array1d({1000});
	ASSERT_EQ(1000,array1d.Length());

	Array<2> array2d({10,20});
	ASSERT_EQ(200,array2d.Length());

	Array<3> array3d({100,20,3});
	ASSERT_EQ(6000,array3d.Length());
}

TEST (test_Array, PositionCalculation){
	Array<3> array3d({100,20,3});
	Array<3>::index idx({0,0,1});
	EXPECT_EQ(1, array3d.Position({0,0,1}));
	EXPECT_EQ(4, array3d.Position({0,1,1}));
	EXPECT_EQ(61, array3d.Position({1,0,1}));
	EXPECT_EQ(601, array3d.Position({10,0,1}));
}

TEST (test_Array, IndexCalculation){
	Array<3> array3d({10,20,3});
	Array<3>::index idx;
	EXPECT_EQ(Array<3>::index({0 ,0,1}), array3d.Index(1));
	EXPECT_EQ(Array<3>::index({0 ,1,1}), array3d.Index(4));
	EXPECT_EQ(Array<3>::index({1 ,0,1}), array3d.Index(61));
	EXPECT_EQ(Array<3>::index({10,0,1}), array3d.Index(601));
}



TEST (test_Array, ElementFill){
	Array<3> array3d({100,20,3});
	array3d({10,10,1})=123.456;
	EXPECT_DOUBLE_EQ(123.456, array3d({10,10,1}));
	EXPECT_DOUBLE_EQ(0.0,     array3d({10,11,1}));
}

TEST (test_Array, ForLoop_Values){
	Array<2> array({100,100});

	for(auto&& val : array) {
		val=5.0;
	}
	EXPECT_DOUBLE_EQ(5,array({1,1}));
	double sum=0;
	for(auto&& val : array) {
		sum+=val;
	}
	EXPECT_DOUBLE_EQ(5.0*array.Length(),sum);
}
TEST (test_Array, ForLoop_Index){
	
	Array<2> array({10,10});
	for(auto& idx: array.Dimensions()){
		ASSERT_NO_THROW(array(idx));
	}
}


TEST (test_Array, OutOfRange_exception){
	Array<3> array3d({100,20,3});
	ASSERT_THROW(array3d({1,1,100}),MR_out_of_range);
	ASSERT_THROW(array3d({1,100,1}),MR_out_of_range);
	ASSERT_THROW(array3d({100,1,1}),MR_out_of_range);
	ASSERT_NO_THROW(array3d({99,1,1}));
}

///checks for array interpolation
TEST (test_Array, InterpolationNearest){
	Array<3> array({5,5,5});
	for(auto&& el: array)el=5;

	array({2,2,2})=10;
	for(double x=1.0; x<=3.0;x+=0.1)
		for(double y=1.0; y<=3.0;y+=0.1)
			for(double z=1.0; z<=3.0;z+=0.1){
				double expected=(fabs(x-2)<0.5&&fabs(y-2)<0.5&&fabs(z-2)<0.5)?10:5;
				EXPECT_DOUBLE_EQ(expected,array.Eval({x,y,z}));	
	}
}

TEST (test_Array, BigArrayLoop_value){
	Array<3> array({100,100,100});
	printf("Array length=%ld\n",array.Length());
	for(auto && val: array){
		val++;
	};
	SUCCEED();
}

TEST (test_Array, BigArrayLoop_index){
	Array<3> array({100,100,100});
	printf("Array length=%ld\n",array.Length());
	for(auto && idx: array.Dimensions()){
		array(idx)++;
	};
	SUCCEED();
}

