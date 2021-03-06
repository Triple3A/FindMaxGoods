#include "Root.h"
#include "Tools.h"
#include <iostream>

using namespace std;

Root::Root(string _command, string _folderName, int _testNumber)
{
    command = _command;
    id = to_string(_testNumber);
    strcpy(namedPipe, (FIFO_FILE_PATH + id).c_str());
    directory = INPUTS_PATH + _folderName;
    vector<string> words = Tools::splitByCharacter(command, SPACE);
    goal = words[0];
    provinceCount = 0;
    this->checkDirectory();

}

Root::~Root()
{
    // for(int i = 0 ; i < provinces.size() ; i++)
    //     waitpid(provinces[i], NULL, WNOHANG);
}

void Root::createNamedPipe()
{
    mkfifo(namedPipe, 0666);
}


void Root::checkDirectory()
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
            provinceNames.push_back(fileName);
            provinceCount++;
        }
    }
    closedir(dr);
}

void Root::createProvincePipes()
{
    for (int i = 0; i < provinceCount; i++)
    {
        int fd[2];
        if (pipe(fd) < 0)
        {
            cerr << "can not create pipe " << i << endl;
            return;
        }
        vector<int> fds;
        fds.push_back(fd[0]);
        fds.push_back(fd[1]);
        provincePipes.push_back(fds);
    }
}

void Root::forkProvince()
{
    for (int i = 0; i < provincePipes.size(); i++)
    {

        this->createNamedPipe();

        pid_t pid = fork();
        if (pid < 0)
        {
            cerr << "Cannot fork" << endl;
        }
        else if (pid == 0)
        {
            close(provincePipes[i][WRITE]);
            char *argv[3];
            argv[0] = (char *)PROVINCE_EXEC_PATH;
            argv[1] = (char *)to_string(provincePipes[i][READ]).c_str();
            argv[2] = NULL;
            execv(argv[0], argv);
        }
        else
        {
            close(provincePipes[i][READ]);
            writeOnProvincePipe(i);
            provinces.push_back(pid);
	        // this->createNamedPipe();

            int fd = open(namedPipe, O_RDONLY);

            wait(NULL);


            if (fd == -1)
                cerr << "Pipe havent been made" << endl;
            else
                fds.push_back(fd);
        }
    }
}

void Root::writeOnProvincePipe(int provinceNumber)
{
    char message[2000];
    strcpy(message, (id + SHARP + to_string(provinceNumber) + SHARP + directory + SLASH + provinceNames[provinceNumber] + LESS + command).c_str());
    write(provincePipes[provinceNumber][WRITE], message, strlen(message) + 1);
}

void Root::findGoal()
{
    for(int i = 0; i < fds.size(); i++)
    {
        char cost[100];
        read(fds[i], cost, 100);
        cout << "Root:" << cost << endl;
        close(fds[i]);
        costs.push_back(stoi(cost));
    }
    if(goal == MAX)
        output = Tools::findMax(costs);
    else if(goal == MIN)
        output = Tools::findMin(costs);
}

void Root::showGoal()
{
    // for(int i = 0; i < costs.size(); i++)
    //     cout << costs[i] << endl;
    cout << output << endl;
}