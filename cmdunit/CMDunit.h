#ifndef CMDUNIT_H
#define CMDUNIT_H

#include <string>
#include <vector>
#include <unordered_map>

class FileSystem;
class Shell;
class Command;

class CommandHandler
{
private:

	Shell* shell {nullptr};
	std::unordered_map<std::string, Command*> cmd_mapper = {}; 
	// ^-- Command is a pointer

public:

	CommandHandler(Shell* inp_shell);
	int parse();
	int execute();
	// int execMessage [ optional ]
};


class Command
{
protected:
	
	std::string cmd_key {""};
	int arg_num {1};
	std::string description {""};
	Shell* shell {nullptr};

public:
	
	Command(
		Shell* inp_shell,
		std::string inp_cmd_key, 
		int inp_arg_num, 
		std::string inp_description
	);

	std::string getDescription() { return description; }
	std::string getCMDkey() { return cmd_key; }
	int getArgNum() { return arg_num; }
	virtual int operate(std::vector<std::string> args) = 0;
};

#endif


