#include <string>
#include <vector>
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"
#include "Shutdown.h"


/*
 *
 *   Author: Oyatillo Axadjonov
 *
 * */


ShutdownCommand::ShutdownCommand()
	: Command("shutdown", 0, "Shuts the system down.")
{
	CommandRegistry::registerCommand("shutdown", this);
	CommandRegistry::registerCommand("exit", this);
}

int ShutdownCommand::operate(Shell& shell,
		std::vector<std::string> cmd_args)
{
	return -2;
}

static ShutdownCommand shutdownCommandInstance;
