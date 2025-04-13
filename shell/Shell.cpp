#include <iostream>
#include <string>
#include "../filesystem/FileSystem.h"
#include "../cmdunit/CMDunit.h"
#include "Shell.h"

Shell::Shell(FileSystem* inp_fsystem)
	: fsystem{ inp_fsystem }
{
	cmdHandler = new CommandHandler(this);
	root_dir = inp_fsystem->getRootDir();
	current_dir = root_dir;
	history = FileObject::create("sh_history", root_dir);
}

Shell::~Shell()
{
	fsystem = nullptr;
	delete cmdHandler;
	cmdHandler = nullptr;
	root_dir = nullptr;
	current_dir = nullptr;
	// delete history; --> this is very dangerous piece of code
	// since it deletes history from memory while allowing
	// the parent directory to have it in childObjects vector.
	// In turn, when root dir deconstructor is called, all
	// other directories's are called too. Here, there
	// is an attempt to delete the deleted memory.
	// There are two solutions: just nullify history pointer or 
	// call ::remove(). I choose the second as it is safer.
	history->remove(); // this is for safety;
	history = nullptr;
}

int Shell::startSession()
{
	while (true)
	{
		std::string prompt = name + " ~" +  current_dir->getPath() + " $ ";
		std::cout << prompt;
		std::string user_input = "";
		getline(std::cin, user_input);
		int code = cmdHandler->processCommand(user_input);
		if (code == -2)
		{ return -2; }
	}
}

int Shell::addHistory(const std::string& user_input)
{
	if (user_input.empty()) { return 0; }
	std::string put_enter = (!getHistory().empty()) ? "\n" : "";
	std::string content = put_enter + "$  " + user_input;
	return history->addWrite(content); // returns integer code
}

std::string Shell::getName() const
{ return name; }

DirectoryObject* Shell::getRootDir() const
{ return root_dir; }

DirectoryObject* Shell::getCurrentDir() const
{ return current_dir; }

std::string Shell::getHistory() const
{ return history->read(); }
