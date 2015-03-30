#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <fstream>

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
