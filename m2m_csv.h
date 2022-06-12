#ifndef M2M_CSV_H
#define M2M_CSV_H

#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>   // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream>   // std::stringstream

#include <stdlib.h>
#include <unistd.h>

class M2M_CSV
{
private:
    std::string fileName;
    std::vector<std::string> columns;

public:
    /**
     * @brief Initiate a csv data instance
     *
     * @param fileName
     * path of the csv file
     * @param columns
     * list of column names for the file
     * @return int
     */
    M2M_CSV(const std::string &fileName, const std::vector<std::string> &columns);
    virtual ~M2M_CSV();
    // int Open();
    // void Close();
    int Write(const std::vector<float> &data);
    std::vector<std::vector<float>> *Read(uint16_t col_num);
};

#endif /* M2M_CSV_H */