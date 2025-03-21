#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>
#include <string>
#include <map>

class Channel
{
public:
    std::string getId() { return id; };
    void setId(std::string id);
    std::string getLocation() { return location; };
    void setLocation(std::string location);
    std::string getName() { return name; };
    void setName(std::string name);
    bool getOccupied() { return occupied; };
    void setOccupied(bool occupied);
    uint8_t getShared() { return shared; };
    void setType(std::string type);
    std::string getType() { return type; };

private:
    std::string id;
    std::string location;
    std::string name;
    bool occupied;
    uint8_t shared;
    std::string type;
};

#endif // CHANNEL_H