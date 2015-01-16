#include "gtest/gtest.h"
#include "ArrayT.h"
#include "Interpolator.h"
#include "MRexception.h"
///checks for array interpolation
TEST (test_Interpolation, Nearest){
    Array<3> array({5,5,5});
    for(auto&& el: array)el=-5;
    array({2,2,2})=10;
    array({2,2,3})=0;
    EXPECT_DOUBLE_EQ(10,array.Eval({1.6,1.6,1.6}));
    EXPECT_DOUBLE_EQ(10,array.Eval({2.4,1.6,2.4}));
    EXPECT_DOUBLE_EQ(10,array.Eval({2.4,2.4,2.4}));
    EXPECT_DOUBLE_EQ(-5,array.Eval({2.4,1.4,2.4}));
    EXPECT_DOUBLE_EQ(-5,array.Eval({2.4,2.4,1.4}));
    EXPECT_DOUBLE_EQ( 0,array.Eval({2.4,2.4,2.6}));
    EXPECT_DOUBLE_EQ(-5,array.Eval({1.5,2.5,1.5}));
    EXPECT_DOUBLE_EQ(-5,array.Eval({2.5,2.5,2.5}));
    EXPECT_DOUBLE_EQ(10,array.Eval({1.5,1.5,1.5}));
}

TEST (test_Interpolation, Linear1d){
    Array<1> array({10});
    array({5})= 1;
    array({6})= 2;
    array({7})= 3;
    array({8})= -3;

    auto inter = Interpolation::Linear<1>(array);
    for(auto&& idx: array.Dimensions()){
        EXPECT_DOUBLE_EQ(array(idx),inter.Eval(point<1>(idx)));
    }
}


TEST (test_Interpolation, Linear3d){
    Array<3> array({10,10,10});
    array({2,2,2})= 15;
    array({2,2,3})=-15;
    auto inter = Interpolation::Linear<3>(array);
    for(auto&& idx: array.Dimensions()){
        EXPECT_DOUBLE_EQ(array(idx),inter.Eval(point<3>(idx)));
    }
}
