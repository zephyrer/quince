/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCECORE_APPLICATION_H
#define QUINCECORE_APPLICATION_H

namespace QuinceSystem
{

class MessageDispatcher;

class QUINCECORE_DLLAPI Application
{
public:
    virtual ~Application() {}
    virtual MessageDispatcher & dispatcher() const = 0; 
    explicit Application(int argc, char** argv);

private:
    int mArgc;
    char** mArgv;
};

}

#endif // QUINCECORE_APPLICATION_H
