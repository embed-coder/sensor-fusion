#ifndef LINS355_H
#define LINS355_H

#include <libserial/SerialPort.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>

#define DATA_LEN_AFTER_HEAD 35
#define TIMEOUT_SERIAL_MS 250
#define ACCEL_SCALE 20
#define RATE_SCALE 1260
#define MAG_SCALE 16
#define SENSOR_SCALE 65536

constexpr const char *const SERIAL_PORT_1 = "/dev/ttyUSB0";
constexpr const char *const SERIAL_PORT_2 = "/dev/ttyUSB1";

typedef unsigned char BYTE;

typedef struct LINS355Data
{
    float accelX;
    float accelY;
    float accelZ;
} LINS355Data;

using namespace LibSerial;

class LINS355
{
private:
    LibSerial::SerialPort serialPort;
    std::string deviceName;
    LibSerial::BaudRate baudRate;
    size_t timeoutMS = TIMEOUT_SERIAL_MS; // Specify a timeout value (in milliseconds).

    uint16_t CalcCRC(DataBuffer buf, const uint32_t &num);

public:
    /**
     * @brief Initiate LINS355 device
     *
     * @param fileName
     * path of the serial port
     * @param baudrate
     * serial port communication speed
     * @param
     * timeout for reading in milisecond
     * @return int
     */
    LINS355(const std::string &fileName, const LibSerial::BaudRate &baudRate, size_t ms_timeout);
    virtual ~LINS355();
    int Open();
    void Close();
    bool IsOpen();
    LINS355Data *ReadData();
};

#endif /* LINS355_H */