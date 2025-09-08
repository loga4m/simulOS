#include "Clear.h"

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

ClearCommand::ClearCommand() : Command{"clear", 0, "A command to clear the screen"}
{
    CommandRegistry::registerCommand("clear", this);
}

int ClearCommand::operate(Shell &shell, std::vector<std::string> cmd_args)
{
    if (cmd_args.size() != 0)
    {
        CommandError("This command does not accept any arguments.");
        return -1;
    }

    // Learned from ChatGPT
    std::cout << "\033[?25l";                      // Hide cursor
    std::cout << "\033[2J\033[1;1H" << std::flush; // clears the screen
    std::cout << "\033[?25h";                      // Show cursor back
    return 0;
}

static ClearCommand clearCommandInstance;
