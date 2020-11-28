#include <vector>
#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define CITY_EXEC_PATH "bin/City"

class Province
{
public:
    Province(int);
    ~Province();
    void createNamedPipe();
    void checkDirectory();
    void forkCity();
    void createCityPipes();
    void writeOnCityPipe(int);
    void findGoal();
    void sendGoal();

private:
    int fdRead;
    int fdWrite;
    std::string id;
    std::string parentId;
    char* namedPipe;
    std::string command;
    std::string goal;
    int cityCount;
    std::string directory;
    std::vector<std::string> cityNames;
    std::vector<std::vector<int> > cityPipes;
    std::vector<pid_t> cities;
    std::vector<int> costs;
    int output;
    std::vector<int> fds;
};
