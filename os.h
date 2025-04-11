#ifndef OS_H
#define OS_H
#include "filesystem/FileSystem.h"
#include "shell/Shell.h"

class OS
{
private:
	FileSystem* filesystem{ nullptr };
	Shell* shell{ nullptr };
public:
	OS();
	~OS();
	int start();
	int stop();
};

#endif
