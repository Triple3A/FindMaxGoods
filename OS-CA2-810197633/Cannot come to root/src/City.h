#include <vector>
#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define STORE_EXEC_PATH "bin/Store"

class City
{
public:
    City(int);
    ~City();
    void createNamedPipe();
    void checkDirectory();
    void forkStore();
    void createStorePipes();
    void writeOnStorePipe(int);
    void findGoal();
    void sendGoal();

private:
    int fdRead;
    std::string command;
    std::string goal;
    int storeCount;
    std::string directory;
    std::vector<std::string> storeNames;
    std::vector<std::vector<int> > storePipes;
    std::vector<pid_t> stores;
    std::vector<int> costs;
    int output;
};
