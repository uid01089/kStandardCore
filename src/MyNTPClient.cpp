#include <MyNTPClient.h>
#include <time.h> /* time_t, struct tm, time, localtime, strftime */

MyNTPClient::MyNTPClient(UDP &udp) : NTPClient(udp)
{
}
MyNTPClient::MyNTPClient(UDP &udp, long timeOffset) : NTPClient(udp, timeOffset)
{
}
MyNTPClient::MyNTPClient(UDP &udp, const char *poolServerName) : NTPClient(udp, poolServerName)
{
}
MyNTPClient::MyNTPClient(UDP &udp, const char *poolServerName, long timeOffset) : NTPClient(udp, poolServerName, timeOffset)
{
}
MyNTPClient::MyNTPClient(UDP &udp, const char *poolServerName, long timeOffset, unsigned long updateInterval) : NTPClient(udp, poolServerName, timeOffset, updateInterval)
{
}
MyNTPClient::MyNTPClient(UDP &udp, IPAddress poolServerIP) : NTPClient(udp, poolServerIP)
{
}
MyNTPClient::MyNTPClient(UDP &udp, IPAddress poolServerIP, long timeOffset) : NTPClient(udp, poolServerIP, timeOffset)
{
}
MyNTPClient::MyNTPClient(UDP &udp, IPAddress poolServerIP, long timeOffset, unsigned long updateInterval) : NTPClient(udp, poolServerIP, timeOffset, updateInterval)
{
}

String MyNTPClient::getTimeString()
{
    update();
    time_t rawTime = getEpochTime();
    struct tm *timeInfo = localtime(&rawTime);
    char buffer[80];

    // https://www.cplusplus.com/reference/ctime/strftime/
    strftime(buffer, 80, "%c", timeInfo);

    return String(buffer);
}