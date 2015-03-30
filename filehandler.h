#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::string;

class FileHandler
{
private:
    ofstream *saveToFile;
    ifstream *loadFromFile;
public:
    FileHandler();
    ~FileHandler();
    void SetOfstream(string directory);
    void SetIfstream(string directory);
    void SaveData();
    void LoadData();
};

#endif // FILEHANDLER_H
