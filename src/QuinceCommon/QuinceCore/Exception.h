/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCECORE_EXCEPTION_H
#define QUINCECORE_EXCEPTION_H

namespace QuinceSystem {

class QUINCECORE_DLLAPI Exception
{
public:
	virtual ~Exception() throw() {}
	virtual string what() const throw() {
		return mMsg;
	}
protected:
	Exception(const string &msg) : mMsg(msg) {}

private:
	string mMsg;
};

class QUINCECORE_DLLAPI FatalError : public Exception
{
public:
	FatalError(const string &msg) : Exception(msg) {}
	virtual ~FatalError() throw() {}
};

class QUINCECORE_DLLAPI NullPointer : public FatalError
{
public:
	NullPointer(const string &msg) : FatalError(msg) {}
	virtual ~NullPointer() throw() {}
};

class QUINCECORE_DLLAPI MemoryError : public Exception
{
public:
	MemoryError(const string &msg) : Exception(msg) {}
	virtual ~MemoryError() throw() {}
};

class QUINCECORE_DLLAPI CalculError : public Exception
{
public:
	CalculError(const string &msg) : Exception(msg) {}
	virtual ~CalculError() throw() {}
};


class QUINCECORE_DLLAPI DivideByZero : public CalculError
{
public:
	DivideByZero(const string &msg) : CalculError(msg) {}
	virtual ~DivideByZero() throw() {}
};

class QUINCECORE_DLLAPI NullVector : public CalculError
{
public:
	NullVector(const string &msg) : CalculError(msg) {}
	virtual ~NullVector() throw() {}
};

} // namespace QuinceSystem

#endif // QUINCESYSTEM_EXCEPTION_H
