#ifndef SHELL_H
#define SHELL_H

class FileSystem;
class DirectoryObject;
class FileObject;
class CommandHandler;
class Command;

class Shell
{
private:
	std::string name = "[simulsh@simulos]";
	FileSystem* fsystem{ nullptr };
	CommandHandler* cmdHandler{ nullptr };
	DirectoryObject* root_dir{ nullptr };
	DirectoryObject* current_dir{ nullptr };
	FileObject* history { nullptr };
public:
	Shell(FileSystem* inp_fsystem);
	~Shell();
	
	int startSession();
	int addHistory(const std::string& user_input);
	std::string getName() const;
	DirectoryObject* getRootDir() const;
	DirectoryObject* getCurrentDir() const;
	std::string getHistory() const;
};


#endif
