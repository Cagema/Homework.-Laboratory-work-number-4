#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FindShortWayService.h"

using namespace std;

int main() {

    setlocale(LC_ALL, "rus");
    ifstream file;
    string path = "E:\\Study\\2 kurs\\4 semestr\\aistd\\LaboratoryWork4Clion\\input.txt";
    file.open(path);
    string start;
    string end;

    FindShortWayService searchEngine(file);

    cout << "Enter your start city: ";
    cin >> start;
    cout << "Enter your destination city: ";
    cin >> end;

    searchEngine.findShortWay(start,end);

    file.close();

    /*testing::InitGoogleTest();
    int b = RUN_ALL_TESTS();*/

    return 0;
}