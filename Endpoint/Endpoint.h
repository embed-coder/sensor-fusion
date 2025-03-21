#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <iostream>
#include <string>
#include <map>

enum EndpointType { CLOUD_ENDPOINT, FILE_ENDPOINT };
enum FileType { CSV, JSON, XML };
enum Protocol { HTTPS, KAFKA, MQTTS, OSPLDDS, RTIDDS };

class Endpoint
{
public:
    Endpoint();
    virtual ~Endpoint();
    
    EndpointType getType() { return type; };
    void setType(EndpointType type);
    std::string getLocation() { return location; };
    void setLocation(std::string location) = 0;

private:
    EndpointType type;
    uint32_t inPort;
    std::string location;
};

#endif // ENDPOINT_H