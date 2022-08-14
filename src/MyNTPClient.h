#ifndef MYNTPCLIENT_H
#define MYNTPCLIENT_H

#include <NTPClient.h>

class MyNTPClient : public NTPClient
{
private:
public:
    MyNTPClient(UDP &udp);
    MyNTPClient(UDP &udp, long timeOffset);
    MyNTPClient(UDP &udp, const char *poolServerName);
    MyNTPClient(UDP &udp, const char *poolServerName, long timeOffset);
    MyNTPClient(UDP &udp, const char *poolServerName, long timeOffset, unsigned long updateInterval);
    MyNTPClient(UDP &udp, IPAddress poolServerIP);
    MyNTPClient(UDP &udp, IPAddress poolServerIP, long timeOffset);
    MyNTPClient(UDP &udp, IPAddress poolServerIP, long timeOffset, unsigned long updateInterval);

    String getTimeString();
};

#endif