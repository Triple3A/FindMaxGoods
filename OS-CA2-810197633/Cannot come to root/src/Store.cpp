#include "Store.h"
#include "Tools.h"
#include <iostream>
#include <fstream>

using namespace std;

Store::Store(int _fdRead)
{
    fdRead = _fdRead;
    char message[2048];
    read(fdRead, message, 2048);
    vector<string> words = Tools::splitByCharacter(message, LESS);
    directory = words[0];
    command = words[1];
    words = Tools::splitByCharacter(command, SPACE);
    goal = words[0];
    id = stoi(words[1]);
    startDate = words[2];
    endDate = words[3];
    storeCount = 0;

    this->createNamedPipe();
}

Store::~Store() {}

void Store::createNamedPipe()
{
    mkfifo(STORE_FILE_PATH, 0666);
}

void Store::openCSV()
{
    fstream fin;
    fin.open(directory, ios::in);
    vector<string> row;
    string temp;
    fin >> temp;
    while(fin >> temp)
    {
        row = Tools::splitByCharacter(temp, COMMA);
        string date = row[0];
        int product_id = stoi(row[1]);
        int price = stoi(row[2]);
        if(checkProduct(date, product_id))
            costs.push_back(price);
    }
    fin.close();
}

bool Store::checkProduct(string date, int product_id)
{
    if (product_id == id)
        if (strcmp(startDate.c_str(), date.c_str()) == -1 && strcmp(endDate.c_str(), date.c_str()) == 1)
            return true;
    return false;
}

void Store::findGoal()
{
    if(goal == MAX)
        output = Tools::findMax(costs);
    else if(goal == MIN)
        output = Tools::findMin(costs);
}

void Store::sendGoal()
{
    // for(int i = 0; i < costs.size(); i++)
    //     cout << costs[i] << endl;
    int fd = open(STORE_FILE_PATH, O_WRONLY);
    char cost[100];
    cout << "Store:" << output << endl;
    strcpy(cost, (to_string(output)).c_str());
    write(fd, cost, strlen(cost) + 1);
    close(fd);
}