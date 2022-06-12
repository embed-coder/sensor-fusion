#include "m2m_csv.h"

M2M_CSV::M2M_CSV(const std::string &fileName, const std::vector<std::string> &columns) : fileName(fileName), columns(columns)
{
    std::string line, colname;

    // Create an input filestream
    std::ifstream if_csv(fileName);
    // Make sure the file is open
    if (if_csv.is_open())
    {
        if (if_csv.good())
        {
            // Extract the first line in the file
            std::getline(if_csv, line);

            // Create a stringstream from line
            std::stringstream ss(line);

            std::vector<std::string> columns_from_file;
            // Extract each column name
            while (std::getline(ss, colname, ','))
            {
                columns_from_file.push_back(colname);
            }

            if (!std::equal(columns.begin(), columns.end(), columns_from_file.begin()))
            {
                throw std::runtime_error("File exists with incorrect colum names");
            }

            if_csv.close();
            return;
        }
        else
        {
            throw std::runtime_error("File error!");
        }
    }

    std::cout << "Create column" << std::endl;
    // Create an output filestream object
    std::ofstream of_csv(fileName);
    // Send column names to the stream
    for (int j = 0; j < columns.size(); ++j)
    {
        std::cout << columns.at(j);
        of_csv << columns.at(j);
        if (j != columns.size() - 1)
        {
            std::cout << ", ";
            of_csv << ","; // No comma at end of line
        }
    }
    of_csv << "\n";
    of_csv.close();
}
M2M_CSV::~M2M_CSV() {}

int M2M_CSV::Write(const std::vector<float> &data)
{
    // Create an output filestream object
    std::ofstream of_csv(fileName, std::ios_base::app);

    // Make sure the file is open
    // if (!of_csv.is_open())
    //     throw std::runtime_error("Could not open file");

    // Send column names to the stream
    for (int j = 0; j < data.size(); ++j)
    {
        of_csv << data.at(j);
        if (j != data.size() - 1)
            of_csv << ","; // No comma at end of line
    }
    of_csv << "\n";
    of_csv.close();

    return EXIT_SUCCESS;
}

std::vector<std::vector<float>> *M2M_CSV::Read(uint16_t col_num)
{
    std::vector<std::vector<float>> *ret_data = new std::vector<std::vector<float>>(col_num);
    std::string line, col_name;
    uint8_t col_i;
    float val;

    // Create an input filestream
    std::ifstream if_csv(fileName);
    // Make sure the file is open
    if (!if_csv.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    if (if_csv.good())
    {
        // Extract the first line in the file
        std::getline(if_csv, col_name);
        if (!col_name.size())
        {
            std::cout << "File empty" << std::endl;
            return NULL;
        }

        while (std::getline(if_csv, line))
        {
            // Create a stringstream of the current line
            std::stringstream ss(line);

            // Extract each integer
            while (ss >> val)
            {
                ret_data->at(col_i++).push_back(val);

                // If the next token is a comma, ignore it and move on
                if (ss.peek() == ',')
                    ss.ignore();
            }
            col_i = 0;
        }

        if_csv.close();
    }
    else
    {
        std::cout << "File doesnot exist" << std::endl;
    }

    return ret_data;
}