#include <cstdlib>
#include <fstream>
#include <iostream>
#include <thread>
#include <mutex>

#include <unistd.h>

#include "LINS355.h"
#include "m2m_csv.h"

#define DEVICE_FILE "/dev/ttyUSB0"
#define DATA_FILE "data.csv"

std::vector<std::vector<float>> data_queue;
std::mutex mtx; // mutex for critical section

void read_from_device(LINS355 *device)
{
    LINS355Data *lins355_data;
    std::vector<float> write_data;

    while (true)
    {
        if (device->IsOpen())
        {
            lins355_data = device->ReadData();
        }
        else
        {
            std::cout << "Failed to open the serial port" << std::endl;
        }
        if (lins355_data)
        {
            std::cout << "Accel x: " << lins355_data->accelX << std::endl;
            write_data.push_back(lins355_data->accelX);
            std::cout << "Accel y: " << lins355_data->accelY << std::endl;
            write_data.push_back(lins355_data->accelY);
            std::cout << "Accel z: " << lins355_data->accelZ << std::endl;
            write_data.push_back(lins355_data->accelZ);
            mtx.lock();
            data_queue.push_back(write_data);
            mtx.unlock();
            write_data.clear();
        }
        usleep(1000);
    }
}

void write_2_csv(M2M_CSV *csv_service)
{
    while (true)
    {
        mtx.lock();
        if (data_queue.empty() == false)
        {
            csv_service->Write(data_queue.back());
            data_queue.pop_back();
        }
        mtx.unlock();
        usleep(1000);
    }
}

int main(int argc, char **argv)
{
    LINS355Data *lins355_data;
    LINS355 *lins355_device = new LINS355(DEVICE_FILE, LibSerial::BaudRate::BAUD_115200, 100);

    std::vector<std::string> columns{"Acc_x", "Acc_y", "Acc_z"};
    M2M_CSV *m2m_csv = new M2M_CSV(DATA_FILE, columns);
    std::vector<float> write_data;

    std::thread lins355_thread(read_from_device, lins355_device);
    std::thread csv_thread(write_2_csv, m2m_csv);

    while (true)
    {
        usleep(1000);
    }

    lins355_thread.join();
    csv_thread.join();

    // Successful program completion.
    std::cout
        << "The example program successfully completed!" << std::endl;
    return EXIT_SUCCESS;
}
