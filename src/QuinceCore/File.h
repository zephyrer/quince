/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCECORE_FILE_H
#define QUINCECORE_FILE_H

namespace QuinceSystem
{

	class QUINCECORE_DLLAPI File
	{
	public:
		File();
		File(const std::string& file_path);
		File(const File& file);
		virtual ~File();
	protected:
		std::string mFilePath;
		std::string mPathName;
		std::string mFileName;
		std::string mBaseName;
		std::string mExtension;
	};

}

#endif // QUINCECORE_FILE_H
