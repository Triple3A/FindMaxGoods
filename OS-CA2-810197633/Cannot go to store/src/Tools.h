#ifndef TOOLS
#define TOOLS
#include <string>
#include <vector>
#define SPACE ' '
#define SLASH '/'
#define LESS '<'
#define COMMA ','
#define DOT '.'
#define SHARP '#'
#define EMPTY_STRING ""
#define DATABASE_FORMAT ".csv"
#define INPUTS_PATH "input/"
#define FIFO_FILE_PATH "namedPipe/"
#define PROVINCE_FILE_PATH "namedPipe/p"
#define CITY_FILE_PATH "namedPipe/c"
#define STORE_FILE_PATH "namedPipe/s"
#define MAX "MAX"
#define MIN "MIN"
#define READ 0
#define WRITE 1


class Tools
{
public:
    static std::vector<std::string> openFile(std::string);
    static std::vector<std::string> splitByCharacter(std::string, char);
    static bool doesStringContainsChar(std::string, char);
    static int findMin(std::vector<int>);
    static int findMax(std::vector<int>);
};
#endif
