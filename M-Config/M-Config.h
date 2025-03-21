#ifndef MCONFIG_H
#define MCONFIG_H

#include "../Channel/Channel.h"
#include "../Device/Device.h"
#include "../Endpoint/Endpoint.h"

class M-Config {
public:
    // Public method to access the instance of the class
    static M-Config& getInstance() {
        static M-Config instance;
        return instance;
    }

    // Delete copy constructor and assignment operator
    M-Config(const M-Config&) = delete;
    M-Config& operator=(const M-Config&) = delete;

    Channel *getChannels();
    void registerChannel(Channel channel);
    Device *getDevices();
    void registerDevice(Device device);
    Endpoint *getEndpoints();
    void regiterEndpoint(Endpoint endpoint);

private:
    // Private constructor so that no objects can be created
    M-Config() = default;
};

#endif // MCONFIG_H