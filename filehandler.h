#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::string;


#define     LOADING_OK          true
#define     SAVING_OK           true
#define     FILE_EMPTY          false
#define     FILE_NOT_OPENED     false


class FileHandler
{
protected:
    ofstream *saveToFile;
    ifstream *loadFromFile;
public:
    FileHandler();
    ~FileHandler();
    void SetOfstream(string directory, ofstream *stream);
    bool SetIfstream(string directory, std::ifstream *stream);
    bool SaveData(string data);
    bool LoadData(string &data);
};

#endif // FILEHANDLER_H
