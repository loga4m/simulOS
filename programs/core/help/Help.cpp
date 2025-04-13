#include <iostream>
#include <string>
#include <vector>
#include "Help.h"
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"

HelpCommand::HelpCommand()
	: Command{ "help", -1, "A program that fetches information about specified commands" }
{
	CommandRegistry::registerCommand("help", this);
}

int HelpCommand::operate(Shell& shell, std::vector<std::string> cmd_args)
{
	HelpProgram* program = new HelpProgram();
	int code = program->run(shell, cmd_args);
	return code;
}

int HelpProgram::run(const Shell& shell, std::vector<std::string> cmd_args)
{
	if (cmd_args.empty())
	{
		std::cout << "help: No arguments provided." << std::endl;
		return -1;
	}
	std::cout << std::endl;
	for (std::string arg: cmd_args)
	{
		Command* cmd = CommandRegistry::getCommand(arg);
		if (!cmd)
		{
			std::cout << "help: Command '" << arg << "' not found." << std::endl;
			continue;
		}
		std::cout << "help----" << cmd->getKey() << "----" << std::endl; 
		std::cout << "Number of allowed arguments (-1 : means any): " << cmd->getArgNum() << std::endl;
		std::cout << "----Description----" << std::endl;
		std::cout << cmd->getDescription() << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return 0;
}


static HelpCommand helpCommanInstance;
