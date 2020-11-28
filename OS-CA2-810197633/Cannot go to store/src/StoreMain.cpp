#include "Store.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "In Store" << endl;
    int fdRead = atoi(argv[1]);
    Store store(fdRead);
    store.openCSV();
    store.findGoal();
    store.sendGoal();
}