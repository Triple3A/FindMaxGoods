#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Root.h"
#include "Tools.h"

using namespace std;

int main(int argc, char *argv[])
{
    string fileName = argv[1];
    string folderName = argv[2];
    vector<string> commands = Tools::openFile(INPUTS_PATH + fileName);
    for (int i = 0; i < commands.size(); i++)
    {
        Root root(commands[i], folderName);
        root.createProvincePipes();
        root.forkProvince();
        root.findGoal();
        root.showGoal();
    }
}
