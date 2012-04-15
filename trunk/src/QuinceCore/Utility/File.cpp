/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#include "Stdafx.h"
#include "File.h"

using namespace std;
using namespace QuinceSystem;

File::File()
	: mFilePath(""), 
	  mPathName(""),
	  mFileName(""),
	  mBaseName(""),
	  mExtension("")
{
}

File::File(const string& file_path)
	: mFilePath(""),
	  mPathName(""),
	  mFileName(""),
	  mBaseName(""),
	  mExtension("")
{
}

File::File(const File& file)
	: mFilePath(file.mFilePath),
	  mPathName(file.mPathName),
	  mFileName(file.mFileName),
	  mBaseName(file.mBaseName),
	  mExtension(file.mExtension)
{
}

File::~File()
{
}
