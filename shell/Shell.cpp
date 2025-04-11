#include "../filesystem/FileSystem.h"
#include "../cmdunit/CMDunit.h"
#include "Shell.h"
#include <iostream>

Shell::Shell(FileSystem* inp_filesystem)
	: filesystem{ inp_filesystem }
{
	cmd_handler = new CommandHandler(this);
};


Shell::~Shell()
{
	delete cmd_handler;
}

int Shell::startSession()
{
	while (true)
	{
		std::string user_prompt = "";
		std::cout << shell_prompt;
		std::getline(std::cin, user_prompt);
		if (user_prompt == "-2") { return -2; }
	}
}

