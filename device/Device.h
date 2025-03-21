#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>
#include <map>

#include "../Channel/Channel.h"
#include "../Endpoint/Endpoint.h"

enum DeviceStatus { UNCONFIRMED, CONNECTED, DISCONNECTED };

class Device
{
public:
    Device();
    virtual ~Device();

    std::string getId() { return id; };
    std::string setId() { return id; };
    std::string getType() { return type; };
    std::string setType() { return type; };
    std::string getBrand() { return brand; };
    std::string setBrand() { return brand; };
    std::string getModel() { return model; };
    std::string setModel() { return model; };
    std::string getSerialNumber() { return serialNumber; };
    std::string setSerialNumber() { return serialNumber; };
    std::string getName() { return name; };
    std::string setName() { return name; };
    virtual uint8_t Open() = 0;
    virtual uint8_t Setup() = 0;
    virtual uint8_t Close() = 0;
    virtual void* GetData() = 0;
    virtual void* SetData(void* data) = 0;
    virtual DeviceStatus getStatus() = 0;

private:
    std::string id;
    std::string type;
    std::string brand;
    std::string model;
    std::string serialNumber;
    std::string name;
    Channel channel;
    Endpoint endpoint;
    uint32_t interval;
    DeviceStatus status;
    std::map<std::string, std::string> meta;
    std::map<std::string, uint8_t> data_tag;
};

#endif /* DEVICE_H */