#ifndef OS_H
#define OS_H

class FileSystem;
class Shell;

class OS
{
private:
	FileSystem* fsystem{ nullptr };
	Shell* shell{ nullptr };
public:
	OS();
	~OS();
	int start();
	int stop();
};

#endif
