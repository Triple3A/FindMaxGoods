#include "City.h"
#include "Tools.h"
#include <iostream>

using namespace std;

City::City(int _fdRead)
{
    fdRead = _fdRead;
    char message[2048];
    read(fdRead, message, 2048);
    cout << message << endl;

    vector<string> dir = Tools::splitByCharacter(message, SHARP);
    parentId = dir[0];
    id = dir[1];

    namedPipe = (char*)(FIFO_FILE_PATH + parentId + id).c_str();

    char* pipe;
    pipe = (char*)(FIFO_FILE_PATH + parentId).c_str();
    // strcpy(pipe, (FIFO_FILE_PATH + parentId).c_str());
    fdWrite = open(pipe, O_WRONLY);

    vector<string> words = Tools::splitByCharacter(dir[2], LESS);
    directory = words[0];
    command = words[1];

    words = Tools::splitByCharacter(command, SPACE);
    goal = words[0];
    storeCount = 0;

    this->checkDirectory();
}

City::~City()
{
    // for(int i = 0 ; i < stores.size() ; i++)
    //     waitpid(stores[i], NULL, WNOHANG);
}

void City::createNamedPipe()
{
	mkfifo(namedPipe, 0666);
}

void City::checkDirectory()
{
    struct dirent *de;
    DIR *dr = opendir(directory.c_str());
    if (dr == NULL)
        return;
    while ((de = readdir(dr)) != NULL)
    {
        string fileName = de->d_name;
        size_t found;
        found = fileName.find(DATABASE_FORMAT);
        if(found != string::npos)
        {
        	cout << "Store:" << fileName << endl;
            storeNames.push_back(fileName);
            storeCount++;
        }
    }
    closedir(dr);
}

void City::createStorePipes()
{
    for (int i = 0; i < storeCount; i++)
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
        storePipes.push_back(fds);
    }
}

void City::forkStore()
{
    for (int i = 0; i < storePipes.size(); i++)
    {
        this->createNamedPipe();

        pid_t pid = fork();
        if (pid < 0)
        {
            cerr << "Cannot fork" << endl;
        }
        else if (pid == 0)
        {
            close(storePipes[i][WRITE]);
            char *argv[3];
            argv[0] = (char *)STORE_EXEC_PATH;
            argv[1] = (char *)to_string(storePipes[i][READ]).c_str();
            argv[2] = NULL;
            execv(argv[0], argv);
        }
        else
        {
            close(storePipes[i][READ]);
            writeOnStorePipe(i);
            stores.push_back(pid);
            // this->createNamedPipe();
            int fd = open(namedPipe, O_RDONLY);
            cout << "CITY:" << fd << endl;
            wait(NULL);

            fds.push_back(fd);
            
        }
    }
}

void City::writeOnStorePipe(int storeNumber)
{
    char message[2000];
    strcpy(message, (parentId + id + SHARP + directory + SLASH + storeNames[storeNumber] + LESS + command).c_str());
    write(storePipes[storeNumber][WRITE], message, strlen(message) + 1);
}

void City::findGoal()
{
    for(int i = 0; fds.size(); i++)
    {
        char cost[100];
        read(fds[i], cost, 100);
        cout << "CITY:" << storeNames[i] << ':' << cost << endl;
        close(fds[i]);
        costs.push_back(stoi(cost));
    }
    if(goal == MAX)
        output = Tools::findMax(costs);
    else if(goal == MIN)
        output = Tools::findMin(costs);
}

void City::sendGoal()
{
    // for(int i = 0; i < costs.size(); i++)
    //     cout << costs[i] << endl;
    // int fd = open(CITY_FILE_PATH, O_WRONLY);
    char cost[100];
    strcpy(cost, (to_string(output)).c_str());
    write(fdWrite, cost, strlen(cost) + 1);
    close(fdWrite);
}