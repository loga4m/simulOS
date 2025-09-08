#include <iostream>
#include <string>
#include <vector>

#include "../../../cmdunit/CMDunit.h"
#include "../../../filesystem/FileSystem.h"
#include "../../../shell/Shell.h"

/*
 *
 *  Author: Azizbek
 *  Reviewer & Assitant: Oyatillo
 *
 * */

class Date : public Command
{
  public:
    Date() : Command("date", 0, "Print Current Date")
    {
        CommandRegistry::registerCommand("date", this);
    };
    int operate(Shell &shell, std::vector<std::string> cmd_args) override
    {
        if (cmd_args.size() != 0)
        {
            std::cout << "date: Too many arguments" << std::endl;
            return -1;
        }
        std::cout << getCurrentTime() << std::endl;
        return 0;
    }
};

static Date dateinstence;
