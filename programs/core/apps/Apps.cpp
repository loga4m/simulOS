#include "./Apps.h"
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"
#include <iostream>
#include <vector>
#include <string>

AppsCommand::AppsCommand()
    : Command{ "apps", 0, "a program that lists available programs" } 
{
    CommandRegistry::registerCommand("apps", this);
}

int AppsCommand::operate(Shell& shell, std::vector<std::string> cmd_args)
{
    AppsProgram* program = new AppsProgram();
    int code = program->run();
    delete program;
    program = nullptr;
    return code;
}


int AppsProgram::run()
{
    const std::vector<std::string>& cmd_names = CommandRegistry::getAllCommandNames();
    std::cout << "Available apps (commands):" << std::endl;
    for (int i = 0; i < cmd_names.size(); i++) {
        std::cout << i + 1 << ". " << cmd_names[i] << std::endl;
    }
    return 0;
}

// At the end

static AppsCommand AppsCommandInstance;
// Congrats! Now it should self-register and work!

