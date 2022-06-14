#include <cstdlib>
#include <fstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <ctime>

#include "LINS355.h"
#include "m2m_csv.h"

#define DEVICE_FILE "/dev/ttyUSB0"
#define DATA_FILE "data.csv"
#define SPAN_MINUTES 5 // data file will be create every 5 minutes span window

std::vector<LINS355Data> data_queue;
std::mutex mtx; // mutex for critical section

void read_from_device(LINS355 *device, u_int16_t interval_ms)
{
    LINS355Data *lins355_data;

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
            std::cout << "Timestamp: " << lins355_data->timestamp << std::endl;
            std::cout << "Accel x: " << lins355_data->data.at(0) << std::endl;
            std::cout << "Accel y: " << lins355_data->data.at(1) << std::endl;
            std::cout << "Accel z: " << lins355_data->data.at(2) << std::endl;
            mtx.lock();
            data_queue.push_back(*lins355_data);
            mtx.unlock();
            delete lins355_data;
        }
        usleep(interval_ms * 1000);
    }
}

void write_2_csv(const std::string &data_file_prefix, const uint16_t &span_minute, const std::vector<std::string> &columns)
{
    std::string data_file;
    M2M_CSV *m2m_csv;
    int prev_min = -1;
    std::string yyyy;
    std::string mm;
    std::string dd;
    std::string hh;
    std::string min;
    int tm_min;

    while (true)
    {
        time_t now = time(0);
        tm *gmtm = gmtime(&now);

        if ((gmtm->tm_min % span_minute == 0 && prev_min != gmtm->tm_min) || prev_min == -1)
        {
            if (m2m_csv)
            {
                delete m2m_csv;
            }
            prev_min = gmtm->tm_min;
            yyyy = std::to_string(1900 + gmtm->tm_year);

            mm = (gmtm->tm_mon < 10) ? "0" : "";
            mm.append(std::to_string(gmtm->tm_mon + 1));

            dd = (gmtm->tm_mday < 10) ? "0" : "";
            dd.append(std::to_string(gmtm->tm_mday));

            hh = (gmtm->tm_hour < 10) ? "0" : "";
            hh.append(std::to_string(gmtm->tm_hour));

            tm_min = gmtm->tm_min;
            if (gmtm->tm_min % span_minute != 0)
            {
                tm_min = (tm_min / span_minute) * span_minute;
            }
            min = (tm_min < 10) ? "0" : "";
            min.append(std::to_string(tm_min));

            data_file = data_file_prefix + "_" + yyyy + mm + dd + "_" + hh + min + ".csv";

            std::cout << "data_file: " << data_file << std::endl;

            m2m_csv = new M2M_CSV(data_file, columns);
            data_file.clear();
        }

        if (m2m_csv)
        {
            if (data_queue.empty() == false)
            {
                mtx.lock();
                m2m_csv->Write(data_queue.back());
                data_queue.pop_back();
                mtx.unlock();
            }
        }
        usleep(1000);
    }
}

void help(std::string app_name)
{
    std::cout << app_name << " is the application to read acceleration data from LINS355 device that connect to Serial port \n\
    Usage : " << app_name
              << " [OPTIONS] [Parameters] \n\
                -d <device_file>        The serial port device file \n\
                                        ex: /dev/ttyUSB0 \n\
                -f <data_file_prefix>   The path to the csv data file \n\
                                        ex: data \n\
                                        default: acc_YYYYMMDD_hhmm.csv \n\
                -h                      Display this message \n\
                -i <interval_ms>        [Optional] The interval in milisecond \n\
                                        ex: 100 \n\
                                        default: 10 (10 ms = 0.01 s = 100 Hz)\n";
}

int main(int argc, char **argv)
{
    int opt;
    std::string device_file;
    std::string data_file_prefix = "acc";
    uint16_t interval_ms = 10; // 100 HZ = 0.01 s = 10 ms
    LINS355 *lins355_device;

    std::vector<std::string> columns{"Timestamp (UTC)", "Acc_x", "Acc_y", "Acc_z"};

    if (argc < 2)
    {
        help(argv[0]);
        return EXIT_FAILURE;
    }
    else
    {
        while ((opt = getopt(argc, argv, "d:f:hi:")) != -1)
        {
            switch (opt)
            {
            case 'd':
                device_file = optarg;
                break;
            case 'f':
                data_file_prefix = optarg;
                break;
            case 'h':
                help(argv[0]);
                return EXIT_SUCCESS;
            case 'i':
                interval_ms = atoi(optarg);
                break;
            default:
                std::cerr << "Run \"" << argv[0] << " -h\" for help" << std::endl;
                return EXIT_FAILURE;
            }
        }
    }

    if (device_file.empty())
    {
        std::cerr << "No input for serial port" << std::endl;
        std::cerr << "Run \"" << argv[0] << " -h\" for help" << std::endl;
        return EXIT_FAILURE;
    }

    lins355_device = new LINS355(device_file, LibSerial::BaudRate::BAUD_115200, 100);

    std::thread lins355_thread(read_from_device, lins355_device, interval_ms);
    std::thread csv_thread(write_2_csv, data_file_prefix, SPAN_MINUTES, columns);

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
