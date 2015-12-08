#include "../headers/CMacros.h"

void mySleep(int sleepMs)
{
#ifdef __linux__
    usleep(sleepMs * 1000);
#endif
#ifdef _WIN32
    Sleep(sleepMs);
#endif
}
