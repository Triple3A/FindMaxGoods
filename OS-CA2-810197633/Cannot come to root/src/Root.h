#include <vector>
#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define PROVINCE_EXEC_PATH "bin/Province"

class Root
{
public:
    Root(std::string, std::string);
    ~Root();
    void checkDirectory();
    void forkProvince();
    void createProvincePipes();
    void writeOnProvincePipe(int);
    void findGoal();
    void showGoal();

private:
    std::string command;
    std::string directory;
    int provinceCount;
    std::vector<std::vector<int> > provincePipes;
    std::vector<std::string> provinceNames;
    std::vector<pid_t> provinces;
    std::string goal;
    int output;
    std::vector<int> costs;
};