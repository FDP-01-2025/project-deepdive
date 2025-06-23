#ifndef READ_DATABASE
#define READ_DATABASE
#include <iostream>
#include <fstream>
#include <string>

void readFile(const std::string &db_deepdive)
{
    std::ifstream file(db_deepdive);
    if (!file.is_open())
    {
        std::cout << "The file could not be opened" << db_deepdive << "\n";
        return;
    }
    std::string line;

    while (std::getline(file, line))
    {
        std::cout << line << "\n";
    }
    file.close();
}

#endif