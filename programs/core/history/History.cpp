#include <iostream>
#include <string>
#include <vector>
#include "History.h"
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"

HistoryCommand::HistoryCommand()
	: Command("history", 0, "Print the history of commands")
{
	static bool registered = CommandRegistry::registerCommand("history", this);
};

int HistoryCommand::operate(const Shell& shell,
		std::vector<std::string> command_vec)
{
	HistoryApp* app = new HistoryApp();
	int code = app->run(shell, command_vec);
	delete app;
	app = nullptr;
	return code;
}

int HistoryApp::run(const Shell& shell, std::vector<std::string> command_v)
{
	std::cout << shell.getHistory() << std::endl;
	return 0;
}

static HistoryCommand historyCommandInstance;
