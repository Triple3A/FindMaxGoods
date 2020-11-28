#include "Province.h"
#include "Tools.h"
#include <iostream>

using namespace std;

Province::Province(int _fdRead)
{
    fdRead = _fdRead;
    char message[2048];
    read(fdRead, message, 2048);
    cout << message << endl;

    vector<string> dir = Tools::splitByCharacter(message, SHARP);
    parentId = dir[0];
    id = dir[1];

    strcpy(namedPipe, (FIFO_FILE_PATH + parentId + id).c_str());


    char* pipee;
    pipee = (char*)(FIFO_FILE_PATH + parentId).c_str();
    // strcpy(pipee, (FIFO_FILE_PATH + parentId).c_str());
    fdWrite = open(pipee, O_WRONLY);

    vector<string> words = Tools::splitByCharacter(dir[2], LESS);
    directory = words[0];
    command = words[1];
    words = Tools::splitByCharacter(command, SPACE);
    goal = words[0];
    cityCount = 0;

    this->checkDirectory();
}

Province::~Province()
{
    // for(int i = 0 ; i < cities.size() ; i++)
    //     waitpid(cities[i], NULL, WNOHANG);
}

void Province::createNamedPipe()
{
    mkfifo(namedPipe, 0666);
}

void Province::checkDirectory()
{
    struct dirent *de;
    DIR *dr = opendir(directory.c_str());
    if (dr == NULL)
        return;
    while ((de = readdir(dr)) != NULL)
    {
        string fileName = de->d_name;
        size_t found;
        found = fileName.find(DOT);
        if(found == string::npos)
        {
            cout << fileName << endl;
            cityNames.push_back(fileName);
            cityCount++;
        }
    }
    closedir(dr);
}

void Province::createCityPipes()
{
    for (int i = 0; i < cityCount; i++)
    {
        int fd[2];
        if (pipe(fd) < 0)
        {
            cerr << "Cannot create pipe " << i << endl;
            return;
        }
        vector<int> fds;
        fds.push_back(fd[0]);
        fds.push_back(fd[1]);
        cityPipes.push_back(fds);
    }
}

void Province::forkCity()
{
    for (int i = 0; i < cityPipes.size(); i++)
    {
        this->createNamedPipe();

        pid_t pid = fork();
        if (pid < 0)
        {
            cerr << "Cannot fork" << endl;
        }
        else if (pid == 0)
        {
            close(cityPipes[i][WRITE]);
            char *argv[3];
            argv[0] = (char *)CITY_EXEC_PATH;
            argv[1] = (char *)to_string(cityPipes[i][READ]).c_str();
            argv[2] = NULL;
            execv(argv[0], argv);
        }
        else
        {
            close(cityPipes[i][READ]);
            writeOnCityPipe(i);
            cities.push_back(pid);
            // this->createNamedPipe();
            int fd = open(namedPipe, O_RDONLY);
            wait(NULL);

            fds.push_back(fd);

        }
    }
}

void Province::writeOnCityPipe(int cityNumber)
{
    char message[2000];
    strcpy(message, (parentId + id + SHARP + to_string(cityNumber) + SHARP + directory + SLASH + cityNames[cityNumber] + LESS + command).c_str());
    write(cityPipes[cityNumber][WRITE], message, strlen(message) + 1);
}

void Province::findGoal()
{
    for(int i = 0; i < fds.size(); i++)
    {
        char cost[100];
        read(fds[i], cost, 100);
        cout << "Province:" << cost << endl;
        close(fds[i]);
        costs.push_back(stoi(cost));
    }
    if(goal == MAX)
        output = Tools::findMax(costs);
    else if(goal == MIN)
        output = Tools::findMin(costs);
}

void Province::sendGoal()
{
    if (fdWrite == -1)
    {
        cerr << "Cannot make pipe" << endl;
        exit(EXIT_FAILURE);
    }
    char cost[20];
    strcpy(cost, (to_string(output)).c_str());
    write(fdWrite, cost, strlen(cost) + 1);
    close(fdWrite);
}