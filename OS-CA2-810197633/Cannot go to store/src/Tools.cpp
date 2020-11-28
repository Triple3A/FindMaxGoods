#include "Tools.h"
#include <iostream>
#include <fstream>

using namespace std;

vector<string> Tools::openFile(string filename)
{
    vector<string> lines;
    string line;
    ifstream file(filename);
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

vector<string> Tools::splitByCharacter(string line, char character)
{
    vector<string> output;
    bool thereIsChar = Tools::doesStringContainsChar(line, character);
    while (thereIsChar == true)
    {
        int characterPosition = line.find(character);
        string subString = line.substr(0, characterPosition);
        string newLine = line.substr(characterPosition + 1);
        line = newLine;
        if (subString != EMPTY_STRING)
            output.push_back(subString);
        thereIsChar = (line.find(character) != string::npos);
    }
    if (line != EMPTY_STRING)
        output.push_back(line);
    return output;
}

bool Tools::doesStringContainsChar(string line, char character)
{
	size_t found = line.find(character);
	return (found != string::npos);
}

int Tools::findMin(vector<int> numbers)
{
    int _min = INT8_MAX;
    for(int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] < _min && numbers[i] != -1)
            _min = numbers[i];
    }
    if (_min == INT8_MAX)
        return -1;
    return _min;
}

int Tools::findMax(vector<int> numbers)
{
    if (numbers.size() == 0)
        return -1;
    int _max = numbers[0];
    for(int i = 1; i < numbers.size(); i++)
    {
        if (numbers[i] > _max)
            _max = numbers[i];
    }
    return _max;
}