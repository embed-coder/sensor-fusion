#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <thread>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../lins355/LINS355.h"
#include "../m2m_csv/m2m_csv.h"

#define DEVICE_FILE_1 "/dev/ttyUSB0"
#define DEVICE_FILE_2 "/dev/ttyUSB1"
#define DATA_FILE "data.csv"

std::string device_file_1;
std::string device_file_2;
std::string data_file;

LINS355Data *lins355_data;
void read_from_device(LINS355 *device, u_int16_t interval_ms)
{
    lins355_data = device->ReadData();
    if (lins355_data)
    {
        std::cout << "Timestamp: " << lins355_data->timestamp << std::endl;
        std::cout << "Accel x: " << lins355_data->data.at(0) << std::endl;
        std::cout << "Accel y: " << lins355_data->data.at(1) << std::endl;
        std::cout << "Accel z: " << lins355_data->data.at(2) << std::endl;
    }
}

void get_env()
{
    const char *env_device_file_1 = std::getenv("DEVICE_FILE_1");
    device_file_1 = (env_device_file_1) ? std::string(env_device_file_1) : DEVICE_FILE_1;
    std::cout << "device_file_1: " << device_file_1 << std::endl;

    const char *env_device_file_2 = std::getenv("DEVICE_FILE_2");
    device_file_2 = (env_device_file_2) ? std::string(env_device_file_2) : DEVICE_FILE_2;
    std::cout << "device_file_2: " << device_file_2 << std::endl;

    const char *env_data_file = std::getenv("DATA_FILE");
    data_file = (env_data_file) ? std::string(env_data_file) : DATA_FILE;
    std::cout << "data_file: " << data_file << std::endl;
}

/**
 * @brief Test OK for all the cases related to LINS355 device
 *  Test env: loop connection between /dev/ttyUSB0 and /dev/ttyUSB1
 * The data will be send from /dev/ttyUSB1 to /dev/ttyUSB0, the received data on /dev/ttyUSB0 will be asserted in the test cases
 */
TEST(LINS355_Device, OK)
{
    get_env();
    std::unique_ptr<LINS355> lins355_test(new LINS355(device_file_1, LibSerial::BaudRate::BAUD_115200, 100));

    // Expect port is openned
    EXPECT_EQ(lins355_test.get()->IsOpen(), true);

    // Read data
    std::thread read_thread(read_from_device, lins355_test.get(), 1);
    // system("bash fake_data.sh LINS355_Device_OK");
    std::string command = "bash fake_data.sh LINS355_Device_OK " + data_file + " " + device_file_2;
    system(command.c_str());
    read_thread.join();

    // Expect not null pointer returned
    EXPECT_NE(lins355_data, nullptr);

    // Expect valid read data
    EXPECT_FLOAT_EQ(lins355_data->data.at(0), 6.499023f); // Accel_X
    EXPECT_FLOAT_EQ(lins355_data->data.at(1), 2.343750f); // Accel_Y
    EXPECT_FLOAT_EQ(lins355_data->data.at(2), 3.203125f); // Accel_Z

    lins355_test.get()->Close();

    // Expect port is closed
    EXPECT_EQ(lins355_test.get()->IsOpen(), false);

    delete lins355_data;
}

/**
 * @brief Open fail on CRC error from data
 *  Test env: loop connection between /dev/ttyUSB0 and /dev/ttyUSB1
 * The data will be send from /dev/ttyUSB1 to /dev/ttyUSB0, the received data on /dev/ttyUSB0 will be asserted in the test cases
 */
TEST(LINS355_Device, FAIL_CRC_Error)
{
    std::unique_ptr<LINS355> lins355_test(new LINS355(device_file_1, LibSerial::BaudRate::BAUD_115200, 100));

    // Expect port is openned
    EXPECT_EQ(lins355_test.get()->IsOpen(), true);

    // Read data
    std::thread read_thread(read_from_device, lins355_test.get(), 1);
    // system("bash fake_data.sh FAIL_CRC");
    std::string command = "bash fake_data.sh FAIL_CRC " + data_file + " " + device_file_2;
    system(command.c_str());
    read_thread.join();

    // Expect null pointer returned because of CRC error
    EXPECT_EQ(lins355_data, nullptr);

    lins355_test.get()->Close();

    // Expect port is closed
    EXPECT_EQ(lins355_test.get()->IsOpen(), false);

    delete lins355_data;
}

/**
 * @brief Test creating, writing, reading data on csv file
 *  Test env: data will be write and read on data.csv
 */
TEST(M2M_CSV, OK)
{
    std::vector<std::string> columns{"Timestamp (UTC)", "Acc_x", "Acc_y", "Acc_z"};
    std::unique_ptr<M2M_CSV> m2m_csv(new M2M_CSV(data_file, columns));
    LINS355Data data{
        .timestamp = "1655163581",
        .data = {
            6.49902f,
            2.34375f,
            3.20312f}};

    // Expect not null pointer returned
    EXPECT_NE(m2m_csv.get(), nullptr);

    // Expect successful writing returned
    EXPECT_EQ(m2m_csv.get()->Write(data), EXIT_SUCCESS);

    std::vector<LINS355Data> *read_data = m2m_csv.get()->Read();

    // Expect valid read data
    EXPECT_EQ(read_data->at(0).timestamp, "1655163581");           // Timestamp
    EXPECT_FLOAT_EQ(read_data->at(0).data.at(0), data.data.at(0)); // Accel_X
    EXPECT_FLOAT_EQ(read_data->at(0).data.at(1), data.data.at(1)); // Accel_Y
    EXPECT_FLOAT_EQ(read_data->at(0).data.at(2), data.data.at(2)); // Accel_Z
}

/**
 * @brief Test on a invalid column names in data file
 *  Test env: an invalid column name will be put into data.csv before running the test case
 */
TEST(M2M_CSV, FAIL_DataFile_Invalid_Column_Name)
{
    std::vector<std::string> columns{"Timestamp (UTC)", "Acc_x", "Acc_y", "Acc_z"};

    // Create an invalid colomn name data file
    std::string command = "bash fake_data.sh FAIL_DataFile_Invalid_Column_Name " + data_file + " " + device_file_2;
    system(command.c_str());

    bool is_m2m_csv_exception = false;
    try
    {
        std::unique_ptr<M2M_CSV> m2m_csv(new M2M_CSV(data_file, columns));
    }
    catch (...)
    {
        std::cout << "Test case: M2M_CSV.FAIL_DataFile_Invalid_Column_Name, as expected" << std::endl;
        is_m2m_csv_exception = true;
    }

    // Expect not null pointer returned
    EXPECT_EQ(is_m2m_csv_exception, true);

    // Delete the invalid file after the test case
    command = "sudo rm -f " + data_file;
    system(command.c_str());
}

/**
 * @brief Test on reading an non-existing data file
 *  Test env: the data file will be deleted before running the reading test case
 */
TEST(M2M_CSV, FAIL_DataFile_Non_Existing)
{
    std::vector<std::string> columns{"Timestamp (UTC)", "Acc_x", "Acc_y", "Acc_z"};
    std::vector<LINS355Data> *read_data;

    std::unique_ptr<M2M_CSV> m2m_csv(new M2M_CSV(data_file, columns));

    // Expect not null pointer returned
    EXPECT_NE(m2m_csv.get(), nullptr);

    // Delete the file before running the test case
    std::string command = "bash fake_data.sh FAIL_DataFile_Non_Existing " + data_file + " " + device_file_2;
    system(command.c_str());

    read_data = m2m_csv.get()->Read();

    // Expect null pointer returned
    EXPECT_EQ(read_data, nullptr);
}