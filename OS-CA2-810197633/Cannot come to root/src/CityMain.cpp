#include "City.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "\nIn City" << endl;
    int fdRead = atoi(argv[1]);
    City city(fdRead);
    city.createStorePipes();
    city.forkStore();
    city.findGoal();
    city.sendGoal();
}