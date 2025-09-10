#ifndef HELP_H
#define HELP_H

#include <string>
#include <vector>

#include "../../../cmdunit/CMDunit.h"

/*
 *
 *   Author: Oyatillo Axadjonov
 *
 * */

class Shell;

class HelpCommand : public Command
{
  public:
    HelpCommand();
    int operate(Shell &shell, std::vector<std::string> cmd_args) override;
};

class HelpProgram
{
  public:
    int run(std::vector<std::string> cmd_args);
};

void printCharNTimes(const int TAB_LEN, const char character);

#endif
