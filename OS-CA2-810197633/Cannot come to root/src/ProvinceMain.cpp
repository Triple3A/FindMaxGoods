#include "Province.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "\n\nIn Province" << endl;
    int fdRead = atoi(argv[1]);
    Province province(fdRead);
    province.createCityPipes();
    province.forkCity();
    province.findGoal();
    province.sendGoal();
}