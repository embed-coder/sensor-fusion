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
#include <iomanip>   //for std::setprecision

#include <stdlib.h>
#include <unistd.h>

#include "LINS355.h"

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
    /**
     * @brief Write LINS355 sensor data to csv file
     *
     * @param data
     * @return int:
     * return 0 as no error
     */
    int Write(const LINS355Data &data);
    /**
     * @brief Read data and return LINS355 data type
     *
     * @return std::vector<LINS355Data>*
     */
    std::vector<LINS355Data> *Read();
};

#endif /* M2M_CSV_H */