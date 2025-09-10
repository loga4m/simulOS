#ifndef ALIAS_H
#define ALIAS_H

#include <vector>
#include <string>

#include "../../../cmdunit/CMDunit.h"

class Shell;
class AliasCommand : public Command
{
public:
    AliasCommand();
    int operate(Shell& shell, std::vector<std::string> cmd_args);
};
class AliasProgram
{
public:
    int run(const std::vector<std::string>& cmd_args);
};

#endif
