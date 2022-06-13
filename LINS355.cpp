#include "LINS355.h"

using namespace LibSerial;

LINS355::LINS355(const std::string &fileName, const LibSerial::BaudRate &baudRate, size_t msTimeout) : deviceName(fileName), baudRate(baudRate), timeoutMS(msTimeout)
{
    serialPort.Open(deviceName);

    // Set the baud rates.
    serialPort.SetBaudRate(baudRate);

    // Set the number of data bits.
    serialPort.SetCharacterSize(CharacterSize::CHAR_SIZE_8);

    // Set the hardware flow control.
    serialPort.SetFlowControl(FlowControl::FLOW_CONTROL_NONE);

    // Set the parity.
    serialPort.SetParity(Parity::PARITY_NONE);

    // Set the number of stop bits.
    serialPort.SetStopBits(StopBits::STOP_BITS_1);
}

LINS355::~LINS355()
{
    serialPort.Close();
}

int LINS355::Open()
{
    if (!serialPort.IsOpen())
    {
        try
        {
            serialPort.Open(deviceName);
        }
        catch (const OpenFailed &)
        {
            std::cerr << "The serial ports did not open correctly." << std::endl;
            return EXIT_FAILURE;
        }
    }
    else
    {
        std::cout << "The serial port was already openned" << std::endl;
    }
    return EXIT_SUCCESS;
}

void LINS355::Close()
{
    serialPort.Close();
}

bool LINS355::IsOpen()
{
    return serialPort.IsOpen();
}

LINS355Data *LINS355::ReadData()
{
    LINS355Data *ret_data = new LINS355Data();
    DataBuffer read_buffer;
    uint16_t sensors[3];
    uint16_t crc;
    std::chrono::_V2::system_clock::time_point timestamp = std::chrono::system_clock::now();

    // Wait for data to be available at the serial port.
    while (!serialPort.IsDataAvailable())
    {
        usleep(1000);
    }

    while (true)
    {
        try
        {
            serialPort.Read(read_buffer, 2, timeoutMS);
        }
        catch (const ReadTimeout &)
        {
            std::cerr << "The Read() call timed out waiting for data." << std::endl;
            return NULL;
        }
        if (0x4C == read_buffer[0] && 0x53 == read_buffer[1])
        {
            try
            {
                serialPort.Read(read_buffer, DATA_LEN_AFTER_HEAD, timeoutMS);
            }
            catch (const ReadTimeout &)
            {
                std::cerr << "The Read() call timed out waiting for data." << std::endl;
                continue;
            }

            for (int i = 0; i < DATA_LEN_AFTER_HEAD; i++)
            {
                printf("%x ", read_buffer[i]);
            }
            std::cout << std::endl;

            crc = (uint16_t)(read_buffer[34] + (read_buffer[33] << 8));
            if (CalcCRC(read_buffer, DATA_LEN_AFTER_HEAD - 2) != crc)
            {
                std::cerr << "CRC error" << std::endl;
                return NULL;
            }

            timestamp = std::chrono::system_clock::now();

            sensors[0] = (uint16_t)(read_buffer[1] + (read_buffer[0] << 8));
            sensors[1] = (uint16_t)(read_buffer[3] + (read_buffer[2] << 8));
            sensors[2] = (uint16_t)(read_buffer[5] + (read_buffer[4] << 8));

            ret_data->timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count());
            // std::cout << "timestamp: " << ret_data->timestamp << std::endl;
            // Accel x, y, z
            // std::cout << "Accel_X: " << sensors[0] * ACCEL_SCALE / SENSOR_SCALE << std::endl;
            ret_data->data.push_back(sensors[0] * ACCEL_SCALE / SENSOR_SCALE);
            // std::cout << "Accel_Y: " << sensors[1] * ACCEL_SCALE / SENSOR_SCALE << std::endl;
            ret_data->data.push_back(sensors[1] * ACCEL_SCALE / SENSOR_SCALE);
            // std::cout << "Accel_Z: " << sensors[2] * ACCEL_SCALE / SENSOR_SCALE << std::endl;
            ret_data->data.push_back(sensors[2] * ACCEL_SCALE / SENSOR_SCALE);
            break;
        }
        usleep(1000);
    }
    return ret_data;
}

uint16_t LINS355::CalcCRC(DataBuffer buf, const uint32_t &num)
{
    int i, j;
    uint16_t crc = 0x1D0F;

    for (i = 0; i < num; i += 1)
    {
        crc ^= (uint16_t)(buf[i] << 8);
        for (j = 0; j < 8; j += 1)
        {
            if ((crc & 0x8000) != 0)
                crc = (uint16_t)((crc << 1) ^ 0x1021);
            else
                crc = (uint16_t)(crc << 1);
        }
    }
    return crc;
}