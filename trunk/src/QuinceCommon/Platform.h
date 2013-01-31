/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCE_PLATFORM_H
#define QUINCE_PLATFORM_H


namespace QuinceSystem
{
	
// Linux
#if defined (__linux__) || defined (__linux)
#define QUINCE_PLATFORM_LINUX
#define QUINCE_PLATFROM_NAME "Linux"

// Mac OS X
#elif defined (__APPLE__) || defined (__MACOSX__) || defined(macosx)
#define QUINCE_PLATFORM_MACOSX
#define QUINCE_PLATFORM_NAME "Mac OS X"

#elif (defined(__CYGWIN32__) || defined(__CYGWIN__))
#define QUINCE_PLATFORM_CYGWIN
#define QUINCE_PLATFORM_NAME "CygWin"      

// Windows
#elif defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || \
      defined(__WIN64__) || defined(_WIN64) || defined(WIN64)
#define QUINCE_PLATFORM_WINDOWS
#define QUINCE_PLATFORM_NAME "Windows"

#endif


class Platform
{
public:
    static const char* name()
    {
        return QUINCE_PLATFORM_NAME;
    }

private:
    Platform();
};

}


#endif // QUINCE_PLATFORM_H
