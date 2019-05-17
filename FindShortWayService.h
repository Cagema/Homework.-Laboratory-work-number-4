#ifndef LAB4_FINDSHORTWAYSERVICE_H
#define LAB4_FINDSHORTWAYSERVICE_H
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

struct Destination
{
    string finish;
    int price;
};

class FindShortWayService
{
//private:
public:
    map <string, vector<Destination> > tripTable;
    const int INF = 1000000;
    int numOfCities = 0;
    map<string, vector<Destination> >:: iterator mapCursor;

    void createTripTable(ifstream& file);

    void createArrWithDefaultVal(int **arr);

    void createAdjMatrix(int **arr);

    void showAdjMatrix(int **arr);

    int determinateCityIndex(string nameOfCity);

    void algorithmFloydWorshel(int **adjMatrix);

//public:

    void showCitiesIndexes(string start, string end, int startIndex, int endIndex){
        cout << "The index of " << start << " = " << startIndex <<endl << "The index of " << end << " = " << endIndex << endl;
    }

    string findCityByIndex(size_t index);

    void showTripTable();

    void findShortWay(string start, string end);

    FindShortWayService(ifstream& file)
    {
        createTripTable(file);
        showTripTable();
    }

    unsigned long getNumOfCities()
    {
        return numOfCities;
    }
};

void FindShortWayService :: createTripTable(ifstream& file)
{
    while (!file.eof())
    {
        string oneString;
        string bufferStr;
        string startPoint;
        string endPoint;
        Destination route1;
        Destination route2;
        string dividedString [4];
        int j = 0;

        getline (file, oneString);
        if (oneString == "")
            getline(file, oneString);
        else
        {
            for (int i = 0; i < oneString.size(); i++)
            {
                char ch = oneString[i];
                if (ch != ';')
                {
                    bufferStr += ch; //character read
                }
                else
                {
                    dividedString[j] = bufferStr;
                    j++;
                    bufferStr = "";
                }
            }
            if (j == 3) dividedString[j] = bufferStr;
            else throw out_of_range("Incorrect file!");
        }
        startPoint = dividedString[0];
        route2.finish = startPoint;

        route1.finish = dividedString[1];
        endPoint = dividedString[1];

        if (dividedString[2] == "N/A" || dividedString[2] == "")    route1.price = INF;
        else    route1.price = atoi(dividedString[2].c_str());

        if (dividedString[3] == "N/A" || dividedString[3] == "")    route2.price = INF;
        else    route2.price = atoi(dividedString[3].c_str());

        tripTable[startPoint].push_back(route1);
        tripTable[endPoint].push_back(route2);
    }
    numOfCities = tripTable.size();
}

void FindShortWayService :: findShortWay(string start, string end)
{
    const unsigned long numOfCities = getNumOfCities();

    int**tripArr = new int*[numOfCities];
    for (size_t i = 0; i < numOfCities; i++)
        tripArr[i] = new int[numOfCities];

    createArrWithDefaultVal(tripArr);

    createAdjMatrix(tripArr);

    int startIndex = determinateCityIndex(start);
    int endIndex = determinateCityIndex(end);

    algorithmFloydWorshel(tripArr);

    if (tripArr[startIndex][endIndex] != INF)
        cout << "The cheapest way: " << start << " -> " << end << " by price =  " << tripArr[startIndex][endIndex] << "$" << endl;
     else
         cout << "Paths from the city " << start << " in " << end << " does not exist" << endl;



    //showAdjMatrix(tripArr);
    //showCitiesIndexes(start, end, startIndex, endIndex);
    //findCityByIndex(startIndex);
}

void FindShortWayService :: createArrWithDefaultVal(int **arr)
{
    for (int i = 0; i < numOfCities; i++)
        for (int j = 0; j < numOfCities; j++)
            arr[i][j] = INF;
}

void FindShortWayService :: createAdjMatrix(int **arr)
{
    map<string, vector<Destination> >:: iterator mapCursor2;
    int i;
    for (mapCursor = tripTable.begin(),i = 0; i < numOfCities ; ++mapCursor, i++)
    {
        vector<Destination>& vec = mapCursor->second;
        vector<Destination>::iterator it;
        for (it = vec.begin(); it != vec.end(); ++it)
        {
            mapCursor2 = tripTable.begin();
            int count = 0;
            while (mapCursor2->first != it->finish)
            {
                count++;
                mapCursor2++;
            }
            arr[i][count] = it->price;
        }
    }
}

void FindShortWayService :: showAdjMatrix(int **arr)
{
    cout << "||";
    for (mapCursor = tripTable.begin(); mapCursor!= tripTable.end(); ++mapCursor)
        cout << mapCursor->first << " || ";
    cout << endl;
    for (int i = 0; i < numOfCities; i++)
    {
        for (int j = 0; j < numOfCities; j++)
        {
            if (i == j)
                cout << "0 ";
            else
            {
                if (arr[i][j] == INF)
                    cout << "-1 ";
                else
                    cout << "" << arr[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void FindShortWayService :: showTripTable()
{
    for (mapCursor = tripTable.begin(); mapCursor != tripTable.end() ; ++mapCursor)
    {
        vector<Destination>& vec = mapCursor->second;
        vector<Destination>::iterator it;
        for (it = vec.begin(); it != vec.end(); ++it)
        {
            cout << mapCursor -> first << " -> ";
            if (it->price == INF)
                cout << it->finish << " = " << "N/A" << endl;
            else
                cout << it->finish << " = " << it->price << endl;
        }
        cout << endl;
    }
}

int FindShortWayService :: determinateCityIndex(string nameOfCity)
{
    int index = 0;
    mapCursor = tripTable.begin();
    while (mapCursor -> first != nameOfCity)
    {
        index++;
        if (index > numOfCities)
            throw out_of_range ("Incorrect city! Program stopped!");
        mapCursor++;
    }
    return index;
}

void FindShortWayService :: algorithmFloydWorshel(int **adjMatrix)
{

    for (size_t k = 0; k < numOfCities; k++)
        for (size_t i = 0; i < numOfCities; i++)
            for (size_t j = 0; j < numOfCities; j++)
                if (adjMatrix[i][k] + adjMatrix[k][j] < adjMatrix[i][j] && (i != j))
                    adjMatrix[i][j] = adjMatrix[i][k] + adjMatrix[k][j];

}

string FindShortWayService ::findCityByIndex(size_t index)
{
    if (index < numOfCities)
    {
        int i = 0;
        for (mapCursor = tripTable.begin(); i!= index; i++)
            mapCursor++;
        return mapCursor->first;
    }
    return "";
}

#endif //LAB4_FINDSHORTWAYSERVICE_H
