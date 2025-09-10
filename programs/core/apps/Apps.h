#ifndef APPS_H // use guards, please!
#define APPS_H

#include <string>
#include <vector>

#include "../../../cmdunit/CMDunit.h"

class Shell;

class AppsCommand : public Command
{
public:
    AppsCommand(); // constructor
    int operate(Shell& shell, std::vector<std::string> cmd_args);
};

class AppsProgram
{
public:
    int run();
};

#endif
