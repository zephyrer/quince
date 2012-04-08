/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCECORE_APPLICATION_H
#define QUINCECORE_APPLICATION_H

namespace QuinceSystem
{

class Logger;
class MessageDispatcher;

class QUINCECORE_DLLAPI Application
{
public:
    virtual ~Application() {}
    virtual MessageDispatcher & dispatcher() const = 0;
    virtual Logger & logger() const = 0;   
protected:
    explicit Application(int argc, char** argv);

    int mArgc;
    char** mArgv;
};

}

#endif // QUINCECORE_APPLICATION_H
