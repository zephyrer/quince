/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCECORE_FILE_H
#define QUINCECORE_FILE_H

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable: 4251)
#endif 

namespace QuinceSystem
{

    class QUINCECORE_DLLAPI File
    {
    public:
	File();
	File(const std::string& file_path);
	virtual ~File();

    public:
        string filePath(bool absolute = false) const;
        string pathName(bool absolute = false) const;
        string fileName() const;
        string baseName() const;
        string extension(bool complete = false) const;

        size_t byteSize() const;
        bool isFile() const;
        bool exists() const;
        bool parse(const string& file_path);

    public:
        static string Separator();
    private:
	string mFilePath;
	string mPathName;
	string mFileName;
	string mBaseName;
	string mExtension;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif // QUINCECORE_FILE_H
