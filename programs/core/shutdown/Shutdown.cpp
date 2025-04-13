#include <string>
#include <vector>
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"
#include "Shutdown.h"

ShutdownCommand::ShutdownCommand()
	: Command("shutdown", 0, "Shuts the system down.")
{
	CommandRegistry::registerCommand("shutdown", this);
	CommandRegistry::registerCommand("exit", this);
}

int ShutdownCommand::operate(const Shell& shell,
		std::vector<std::string> command_vec)
{
	return -2;
}

static ShutdownCommand shutdownCommandInstance;
