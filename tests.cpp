
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include "../FindShortWayService.h"
using namespace std;

using testing::Eq;

namespace {
    class ClassDeclaration: public testing::Test{
    public:
        //initialization of object that will be used in test

        ifstream input;
        ClassDeclaration(){
            string path = "E:\\Study\\2 kurs\\4 semestr\\aistd\\LaboratoryWork4Clion\\test\\inputForTest.txt";
            input.open(path);
        }
    };
}

TEST_F(ClassDeclaration, test_createTripTable){
    FindShortWayService service(input);
    ASSERT_EQ(service.getNumOfCities(), 4);
}
TEST_F(ClassDeclaration, test_createArrWithDefoultVal){
    FindShortWayService service(input);
    int**tripArr = new int*[service.getNumOfCities()];
    for (size_t i = 0; i < service.getNumOfCities(); i++)
        tripArr[i] = new int[service.getNumOfCities()];
    service.createArrWithDefaultVal(tripArr);
    for(int i = 0; i < service.getNumOfCities(); i++){
        for(int j = 0; j < service.getNumOfCities(); j++){
            ASSERT_EQ(tripArr[i][j],1000000);
        }
    }
    input.close();
}

TEST_F(ClassDeclaration, test_createAdjMatrix){
    FindShortWayService service(input);
    int**tripArr = new int*[service.getNumOfCities()];
    for (size_t i = 0; i < service.getNumOfCities(); i++)
        tripArr[i] = new int[service.getNumOfCities()];
    service.createArrWithDefaultVal(tripArr);
    service.createAdjMatrix(tripArr);
    ASSERT_EQ(tripArr[0][0],1000000);
    ASSERT_EQ(tripArr[0][1],35);
    ASSERT_EQ(tripArr[0][2],1000000);
    ASSERT_EQ(tripArr[0][3],8);
    ASSERT_EQ(tripArr[1][0],40);
    ASSERT_EQ(tripArr[1][1],1000000);
    ASSERT_EQ(tripArr[1][2],20);
    ASSERT_EQ(tripArr[1][3],1000000);
    ASSERT_EQ(tripArr[2][0],14);
    ASSERT_EQ(tripArr[2][1],10);
    ASSERT_EQ(tripArr[2][2],1000000);
    ASSERT_EQ(tripArr[2][3],20);
    ASSERT_EQ(tripArr[3][0],13);
    ASSERT_EQ(tripArr[3][1],1000000);
    ASSERT_EQ(tripArr[3][2],1000000);
    ASSERT_EQ(tripArr[3][3],1000000);

}

TEST_F(ClassDeclaration, test_determinateCityIndex){
    FindShortWayService service(input);
    ASSERT_EQ(service.determinateCityIndex("Khabarovsk"), 0);
    ASSERT_EQ(service.determinateCityIndex("Moscow"), 1);
    ASSERT_EQ(service.determinateCityIndex("St.Petersburg"), 2);
    ASSERT_EQ(service.determinateCityIndex("Vladivostok"), 3);
    EXPECT_THROW(service.determinateCityIndex("Брюховецкая"), out_of_range);
}

TEST_F(ClassDeclaration, test_fordBellmanAlgorithm){
    FindShortWayService service(input);
    int**tripArr = new int*[service.getNumOfCities()];
    for (size_t i = 0; i < service.getNumOfCities(); i++)
        tripArr[i] = new int[service.getNumOfCities()];
    service.createArrWithDefaultVal(tripArr);
    service.createAdjMatrix(tripArr);
    ASSERT_EQ(tripArr[3][0],13);
    ASSERT_EQ(tripArr[3][1],1000000);
    ASSERT_EQ(tripArr[3][2],1000000);
    service.algorithmFloydWorshel(tripArr);
    ASSERT_EQ(tripArr[3][0],13);
    ASSERT_EQ(tripArr[3][1],48);
    ASSERT_EQ(tripArr[3][2],68);
}
