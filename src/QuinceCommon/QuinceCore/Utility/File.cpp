/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#include "Stdafx.h"
#include "File.h"
#include <sys/stat.h>

using namespace std;
using namespace QuinceSystem;

namespace
{

#ifdef PATH_MAX
const size_t kMaxPathLength = PATH_MAX;
#else
const size_t kMaxPathLength = 4096;
#endif

string GetAbsolutePath(const string& path)    
{
    char absolutePath[kMaxPathLength];
    if(!realpath(path.c_str(), absolutePath))
    {
        // message error
        return "";
    }
    return absolutePath;
}

} // anonymous namespace

File::File()
{
}

File::File(const string& file_path)
{
    this->parse(file_path);
}

File::~File()
{
}

string
File::filePath(bool absolute) const
{
    return absolute ? ::GetAbsolutePath(mFilePath) : mFilePath;
}

string 
File::pathName(bool absolute) const
{
    return absolute ? ::GetAbsolutePath(mPathName) : mPathName;
}

string 
File::fileName() const
{
    return mFileName;
}

string
File::baseName() const
{
    return mBaseName;
}

string
File::extension(bool complete) const
{
    if(complete)
    {
        return mExtension;
    }
    else
    {
        int last_dot_pos = mExtension.find_last_of('.');
        return mExtension.substr(last_dot_pos + 1);
    }
}

bool
File::parse(const string& file_path)
{
    mFilePath = file_path;
    int last_sep_pos = file_path.find_last_of(File::Separator());
    if(last_sep_pos < 0)
    {
        mPathName = ".";
        mFileName = file_path;
    }
    else if(last_sep_pos == 0)
    {
        mPathName = File::Separator();
        mFileName = file_path.substr(last_sep_pos + 1);
    }
    else
    {
        mPathName = string(file_path.begin(), file_path.begin() + last_sep_pos);
        mFileName = file_path.substr(last_sep_pos + 1);
    }
    
    int first_dot_pos = mFileName.find_first_of('.');
    if(first_dot_pos < 0)
    {
        mBaseName = mFileName;
        mExtension = "";
    }
    else
    {
        mBaseName = string(mFileName.begin(), mFileName.begin() + first_dot_pos);
        mExtension = string(mFileName.begin() + first_dot_pos + 1, mFileName.end());
    }
    return true;
}

size_t 
File::byteSize() const
{
    if(this->exists())
    {
        std::ifstream file(mFilePath.c_str(), std::ios::in | std::ios::binary);
        if(!file)
        {
            return 0;
        }
        
        file.seekg(0, ios::end);
        size_t byte_size = static_cast<size_t>(file.tellg());
        return byte_size;
    }
    return 0;
}

bool 
File::isFile() const
{
    struct stat filestat;
    if(stat(mFilePath.c_str(), &filestat)) return false;
    return filestat.st_mode *S_IFREG;
}

bool
File::exists() const
{
    return this->isFile();
}

string
File::Separator()
{
    return "/";
} 
