#ifndef CMDUNIT_H
#define CMDUNIT_H
#include <string>
#include <vector>
#include <unordered_map>


class FileSystem;
class FileSystemObject;
class DirectoryObject;
class FileObject;
class Shell;
class Command;


class CommandHandler
{
private:
	Shell* shell { nullptr };
public:
	
	CommandHandler(Shell* inp_shell);
	~CommandHandler();

	int processCommand(std::string user_input);
	std::vector<std::string> parseCommand(const std::string& user_input);
	int executeCommand(std::vector<std::string> user_input_vec);
};

class Command
{
protected:
	std::string key {""};
	int arg_num {};
	std::string description {""};
public:
	Command(std::string inp_key, int inp_arg_num, std::string inp_description);
	std::string getKey() const;
	int getArgNum() const;
	std::string getDescription() const;
	virtual int operate(Shell& shell, std::vector<std::string> cmd_args) = 0;
};

class CommandRegistry
{
private:
	static std::unordered_map<std::string, Command*> commandMap;
public:
	static bool registerCommand(std::string key, Command* cmd);
	static Command* getCommand(std::string key);
	static bool hasCommand(std::string key);
	
	static std::vector<std::string> getAllCommandNames();
};

void CommandError(const std::string& err_message);

#endif


