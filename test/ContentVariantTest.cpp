#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ContentVariant.h"//../lib/game/include/
#include <iostream>
//#include <vector>
//#include <map>
//#include <string>
using namespace std;

TEST(ContentVariantSuite, testCreation)
{
    dataVariant testStr = "test";
    dataVariant testInt = 7;
    dataVariant testFloat = float(7.5);
    dataVariant testBool = true;

    vector<dataVariant> V;
    V.push_back(1);
    V.push_back(2);
    V.push_back(3);
    dataVariant testVector = V;

    map<string, dataVariant> M;
    M["first"] = 1;
    M["second"] = 2;
    M["third"] = 3;
    dataVariant testMap = M;
    
    EXPECT_EQ(true, true);
}




TEST(ContentVariantSuite, testToStringVisitor)
{
    dataVariant testStr = "test";
    dataVariant testInt = 7;
    dataVariant testFloat = float(7.5);
    dataVariant testBool = true;

    vector<dataVariant> V;
    V.push_back(1);
    V.push_back(2);
    V.push_back(3);
    dataVariant testVector = V;

    map<string, dataVariant> M;
    M["first"] = 1;
    M["second"] = 2;
    M["third"] = 3;
    dataVariant testMap = M;

    EXPECT_EQ(rva::visit(toStringVisitor(), testStr),"test");
    EXPECT_EQ(rva::visit(toStringVisitor(), testInt),"7");
    EXPECT_EQ(rva::visit(toStringVisitor(), testFloat),"7.5");
    EXPECT_EQ(rva::visit(toStringVisitor(), testBool),"true");
    EXPECT_EQ(rva::visit(toStringVisitor(), testVector),"[1, 2, 3]");
    EXPECT_EQ(rva::visit(toStringVisitor(), testMap),"((first: 1), (second: 2), (third: 3))");
}


TEST(ContentVariantSuite, testToIntVisitor)
{
    dataVariant testInt = 7;
    dataVariant testFloat = float(7.5);

    EXPECT_EQ(rva::visit(toIntVisitor(), testInt),7);
    EXPECT_EQ(rva::visit(toIntVisitor(), testFloat),7);
}


TEST(ContentVariantSuite, testToFloatVisitor)
{
    dataVariant testInt = 7;
    dataVariant testFloat = float(7.5);

    EXPECT_FLOAT_EQ (rva::visit(toFloatVisitor(), testInt),7.0);
    EXPECT_FLOAT_EQ (rva::visit(toFloatVisitor(), testFloat),7.5);
}


map<int,int> countIntElements(dataVariant inputVector){
    map<int,int> CountMap;

    vector<dataVariant> dataVariantVector = rva::get<vector<dataVariant>>(inputVector);
    int elementValue;
    for (auto dataVariantElement: dataVariantVector){
        elementValue = rva::visit(toIntVisitor(),dataVariantElement);
        if (CountMap.find(elementValue) == CountMap.end()){
            CountMap[elementValue] = 1;
        }
        else{
            CountMap[elementValue] = CountMap[elementValue]+1;
        }
    }
    return CountMap;
}


TEST(ContentVariantSuite, testShuffleVisitor)
{
    vector<dataVariant> emptyVector;
    dataVariant testEmptyVector = emptyVector;

    rva::visit(shuffleVisitor(), testEmptyVector);
    EXPECT_EQ(rva::get<vector<dataVariant>>(testEmptyVector),emptyVector);


    vector<dataVariant> singleElementVector;
    singleElementVector.push_back(1);
    dataVariant testsingleElementVector = singleElementVector;

    rva::visit(shuffleVisitor(), testsingleElementVector);
    EXPECT_EQ(rva::get<vector<dataVariant>>(testsingleElementVector),singleElementVector);


    //Must push sufficient elements such that the chance of a valid shuffle returning in the original order is negligible
    vector<dataVariant> multiElementVector;
    multiElementVector.push_back(1);
    multiElementVector.push_back(2);
    multiElementVector.push_back(3);
    multiElementVector.push_back(4);
    multiElementVector.push_back(5);
    multiElementVector.push_back(6);
    multiElementVector.push_back(7);
    multiElementVector.push_back(8);
    dataVariant testMultiElementVector = multiElementVector;

    rva::visit(shuffleVisitor(), testMultiElementVector);

    EXPECT_NE(rva::get<vector<dataVariant>>(testMultiElementVector),multiElementVector);
    EXPECT_EQ(countIntElements(testMultiElementVector),countIntElements(multiElementVector));


    //Must push sufficient elements such that the chance of a valid shuffle returning in the original order is negligible
    vector<dataVariant> repeatElementVector;
    repeatElementVector.push_back(1);
    repeatElementVector.push_back(2);
    repeatElementVector.push_back(2);
    repeatElementVector.push_back(3);
    repeatElementVector.push_back(3);
    repeatElementVector.push_back(3);
    repeatElementVector.push_back(4);
    repeatElementVector.push_back(4);
    repeatElementVector.push_back(4);
    repeatElementVector.push_back(4);
    dataVariant testRepeatElementVector = repeatElementVector;

    rva::visit(shuffleVisitor(), testRepeatElementVector);

    EXPECT_NE(rva::get<vector<dataVariant>>(testRepeatElementVector),repeatElementVector);
    EXPECT_EQ(countIntElements(testRepeatElementVector),countIntElements(repeatElementVector));
}


TEST(ContentVariantSuite, testAddVisitor)
{
    dataVariant testInt1 = 7;
    dataVariant testInt2 = 10;

    dataVariant testFloat1 = float(7.5);
    dataVariant testFloat2 = float(10.5);

    EXPECT_EQ(rva::visit(addVisitor(), testInt1,testInt2),17);


    dataVariant floatToFloatDataVariant =  rva::visit(addVisitor(), testFloat1,testFloat2);
    float convertedFloatToFloat = rva::visit(toFloatVisitor(),floatToFloatDataVariant);
    EXPECT_FLOAT_EQ(convertedFloatToFloat,18.0);

    dataVariant intToFloatDataVariant =  rva::visit(addVisitor(), testInt1,testFloat1);
    float convertedIntToFloat = rva::visit(toFloatVisitor(),intToFloatDataVariant);
    EXPECT_FLOAT_EQ(convertedIntToFloat,14.5);

    dataVariant floatToIntDataVariant =  rva::visit(addVisitor(), testFloat1,testInt2);
    float convertedFloatToInt = rva::visit(toFloatVisitor(),floatToIntDataVariant);
    EXPECT_FLOAT_EQ(convertedFloatToInt,17.5);
}


TEST(ContentVariantSuite, testAppendVisitor)
{
    dataVariant a = "a";
    dataVariant b = "b";
    dataVariant ab = "ab";
    dataVariant strAppendResult = rva::visit(appendVisitor(),a,b);
    EXPECT_EQ(strAppendResult,ab);
    vector<dataVariant> emptyVector;
    dataVariant emptyVectorDataVector = emptyVector;
}


TEST(ContentVariantSuite, testReverseVisitor)
{
    vector<dataVariant> emptyVector;
    dataVariant EmptyVectorDataVariant = emptyVector;

    rva::visit(reverseVisitor(), EmptyVectorDataVariant);
    EXPECT_EQ(rva::get<vector<dataVariant>>(EmptyVectorDataVariant),emptyVector);


    vector<dataVariant> singleElementVector;
    singleElementVector.push_back(1);
    dataVariant singleElementVectorDataVariant = singleElementVector;

    rva::visit(reverseVisitor(), singleElementVectorDataVariant);
    EXPECT_EQ(rva::get<vector<dataVariant>>(singleElementVectorDataVariant),singleElementVector);



    vector<dataVariant> multiElementVector;
    multiElementVector.push_back(1);
    multiElementVector.push_back(2);
    multiElementVector.push_back(3);
    dataVariant multiElementVectorDataVariant = multiElementVector;


    vector<dataVariant> ReverseMultiElementVector;
    ReverseMultiElementVector.push_back(3);
    ReverseMultiElementVector.push_back(2);
    ReverseMultiElementVector.push_back(1);

    rva::visit(reverseVisitor(), multiElementVectorDataVariant);

    EXPECT_EQ(rva::get<vector<dataVariant>>(multiElementVectorDataVariant),ReverseMultiElementVector);

}