#ifndef _CMACROS_H_
#define _CMACROS_H_

#ifdef __linux__
    #include <unistd.h>
#endif
#ifdef _WIN32
    #include <windows.h>
#endif

void mySleep(int sleepMs);

#endif // _CMACROS_H_
