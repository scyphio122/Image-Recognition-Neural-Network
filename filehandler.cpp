#include "filehandler.h"
#include <fstream>
#include <iostream>
using namespace std;

FileHandler::FileHandler()
{

}

FileHandler::~FileHandler()
{

}

/**
 * @brief FileHandler::SetIfstream  -   This function opens the file set in the directory to load from it.
 * @param directory                 -   The directory of the file
 *
 * @param stream                    -   The stream which loadFromFile will point to.
 */
void FileHandler::SetIfstream(string directory, ifstream stream)
{
    this->loadFromFile = &stream;
    this->loadFromFile->open(directory.c_str());
}

/**
 * @brief FileHandler::SetOfstream  -   This function opens the file specified in the directory to save data in it.
 * @param directory                 -   Specified file in the hard drive.If not existing, it will be created.
 * @param stream                    -   The stream which saveToFile will point to.
 */
void FileHandler::SetOfstream(string directory, ofstream stream)
{
    this->saveToFile = &stream;
    this->saveToFile->open(directory.c_str());
}


/**
 * @brief FileHandler::SaveData     -   This function is called to save a piece of data in the file opened by saveToFile. After the piece of saved data it inserts ';' delimiter in the file.  The function checks whether the file was earlier opened. If not, it returns error.
 * @param data                      -   The data which is to be saved
 * @return                          -   SAVING_OK, FILE_NOT_OPENED
 */
bool FileHandler::SaveData(string data)
{
    if(!this->saveToFile->is_open())
    {
        return FILE_NOT_OPENED;
    }
    else
    {
        (*saveToFile)<<data<<';';
        return SAVING_OK;
    }
}
/**
 * @brief FileHandler::LoadData     -   This function is called to load a piece of data until the ';' delimiter is loaded. The data is loaded from the file opened by the loadToFile. If it was not opened, it returns FILE_EMPTY error. If it is end of the file it returns FILE_EMPTY error. If everything is ok, it return LOADING_OK
 * @param data                      - A variable which will be a container for the loaded data
 * @return                          -   LOADING_OK, FILE_EMPTY, FILE_NOT_OPENED
 */
bool FileHandler::LoadData(string &data)
{
    if(!loadFromFile->is_open())
        return FILE_NOT_OPENED;

    string buffer;
    getline(*this->loadFromFile, buffer, ';');

    if(!this->loadFromFile->eof())
    {
        data = buffer;
        return LOADING_OK;
    }
    else
        return FILE_EMPTY;
}
