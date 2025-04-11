#ifndef SHELL_H
#define SHELL_H
#include "../filesystem/FileSystem.h"
#include "../cmdunit/CMDunit.h"
#include <string>

class Shell
{
private:
	std::string name {"simulsh"}; 
	std::string shell_prompt = "[simulsh@simulos]$ ";
	
	FileSystem* filesystem {nullptr};
	CommandHandler* cmd_handler {nullptr};
	
	// FileObject* root_dir {nullptr};
	std::string current_path {"/"};
	// FileObject* current_dir {nullptr;}

	// FileObject history {};
public:
	Shell(FileSystem* inp_filesystem); // Constructor
	~Shell();
	int startSession();
};

#endif
