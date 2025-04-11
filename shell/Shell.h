#ifndef SHELL_H
#define SHELL_H
#include <string>


class FileSystem;
class CommandHandler;
class Command;


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
