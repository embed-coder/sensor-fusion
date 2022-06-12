#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>

#include "../LINS355.h"
#include "../m2m_csv.h"

#define DEVICE_FILE_1 "/dev/ttyUSB0"
#define DEVICE_FILE_2 "/dev/ttyUSB1"
#define DEVICE_FILE_3 "/dev/ttyUSB2"
#define DATA_FILE "data.csv"

/**
 * @brief Test OK for all the cases related to LINS355 device
 *  Test env: loop connection between /dev/ttyUSB0 and /dev/ttyUSB1
 * The data will be send from /dev/ttyUSB1 to /dev/ttyUSB0, the received data on /dev/ttyUSB0 will be asserted in the test cases
 */
TEST(LINS355_Device, OK)
{
    LINS355 *lins355_test = new LINS355(DEVICE_FILE_1, LibSerial::BaudRate::BAUD_115200, 100);
    LINS355Data *lins355_data;

    // Expect not null pointer returned
    EXPECT_NE(lins355_test, nullptr);

    // Expect port is openned
    EXPECT_EQ(lins355_test->Open(), EXIT_SUCCESS);
    EXPECT_EQ(lins355_test->IsOpen(), EXIT_SUCCESS);

    // Read data
    // echo -n -e "\x4C\x53\x53\x30\x1E\x00\x29\x00\x2D\xF3\x3E\x00\x02\xFF\xFE\xFF\xFC\xFD\xB6\xFA\x34\x05\x17\x1E\x74\x1E\x74\x1E\x74\x1E\x74\x29\xF6\x00\x00\x01\x25" > /dev/ttyUSB1
    system("sleep 1 && echo -n -e \"\\x4C\\x53\\x53\\x30\\x1E\\x00\\x29\\x00\\x2D\\xF3\\x3E\\x00\\x02\\xFF\\xFE\\xFF\\xFC\\xFD\\xB6\\xFA\\x34\\x05\\x17\\x1E\\x74\\x1E\\x74\\x1E\\x74\\x1E\\x74\\x29\\xF6\\x00\\x00\\x01\\x25\" > /dev/ttyUSB1");
    lins355_data = lins355_test->ReadData();

    // Expect not null pointer returned
    EXPECT_NE(lins355_data, nullptr);

    // Expect valid read data
    EXPECT_EQ(lins355_data->accelX, 6);
    EXPECT_EQ(lins355_data->accelY, 2);
    EXPECT_EQ(lins355_data->accelZ, 3);

    lins355_test->Close();

    delete lins355_test;
    delete lins355_data;
}

/**
 * @brief Open fail on invalid serial port
 *  Test env: No serial device connected on /dev/ttyUSB2
 * The data will be send from /dev/ttyUSB1 to /dev/ttyUSB0, the received data on /dev/ttyUSB0 will be asserted in the test cases
 */
TEST(LINS355_Device, Open_FAIL)
{
    LINS355 *lins355_test = new LINS355(DEVICE_FILE_3, LibSerial::BaudRate::BAUD_115200, 100);
    LINS355Data *lins355_data;

    // Expect not null pointer returned
    EXPECT_EQ(lins355_test, nullptr);

    // Expect port is openned
    EXPECT_EQ(lins355_test->Open(), EXIT_FAILURE);
    EXPECT_EQ(lins355_test->IsOpen(), EXIT_FAILURE);

    // Read data
    // echo -n -e "\x4C\x53\x53\x30\x1E\x00\x29\x00\x2D\xF3\x3E\x00\x02\xFF\xFE\xFF\xFC\xFD\xB6\xFA\x34\x05\x17\x1E\x74\x1E\x74\x1E\x74\x1E\x74\x29\xF6\x00\x00\x01\x25" > /dev/ttyUSB1
    system("sleep 1 && echo -n -e \"\\x4C\\x53\\x53\\x30\\x1E\\x00\\x29\\x00\\x2D\\xF3\\x3E\\x00\\x02\\xFF\\xFE\\xFF\\xFC\\xFD\\xB6\\xFA\\x34\\x05\\x17\\x1E\\x74\\x1E\\x74\\x1E\\x74\\x1E\\x74\\x29\\xF6\\x00\\x00\\x01\\x25\" > /dev/ttyUSB1");
    lins355_data = lins355_test->ReadData();

    // Expect not null pointer returned
    EXPECT_NE(lins355_data, nullptr);

    // Expect valid read data
    EXPECT_EQ(lins355_data->accelX, 6);
    EXPECT_EQ(lins355_data->accelY, 2);
    EXPECT_EQ(lins355_data->accelZ, 3);

    lins355_test->Close();

    delete lins355_test;
    delete lins355_data;
}