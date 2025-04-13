#ifndef HELP_H
#define HELP_H

#include <string>
#include <vector>
#include "../../../cmdunit/CMDunit.h"

class Shell;

class HelpCommand : public Command
{
public:
	HelpCommand();
	int operate(const Shell& shell, std::vector<std::string> cmd_args) override;
};

class HelpProgram
{
public:
	int run(const Shell& shell, std::vector<std::string> cmd_args);	
};

#endif
