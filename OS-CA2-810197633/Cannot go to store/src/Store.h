#include <vector>
#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

class Store
{
public:
    Store(int);
    ~Store();
    void openCSV();
    bool checkProduct(std::string, int);
    void findGoal();
    void sendGoal();

private:
    int fdRead;
    int fdWrite;
    std::string parentId;
    std::string command;
    std::string goal;
    int storeCount;
    std::string directory;
    std::vector<std::string> storeNames;
    std::vector<std::vector<int> > storePipes;
    std::vector<pid_t> stores;
    std::vector<int> costs;
    int output;
    int id;
    std::string startDate;
    std::string endDate;
};
