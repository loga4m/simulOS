#include "History.h"

#include <iostream>
#include <string>
#include <vector>

#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"

/*
 *
 *   Author: Oyatillo Axadjonov
 *
 * */

HistoryCommand::HistoryCommand() : Command("history", 0, "Print the history of commands")
{
    CommandRegistry::registerCommand("history", this);
};

int HistoryCommand::operate(Shell &shell, std::vector<std::string> cmd_args)
{
    HistoryApp *app = new HistoryApp();
    int code = app->run(shell, cmd_args);
    delete app;
    app = nullptr;
    return code;
}

int HistoryApp::run(const Shell &shell, std::vector<std::string> args)
{
    std::cout << shell.getHistory() << std::endl;
    return 0;
}

static HistoryCommand historyCommandInstance;
