#include <iostream>
#include <string>
#include <vector>

#include "../../../cmdunit/CMDunit.h"
#include "../../../filesystem/FileSystem.h"
#include "../../../shell/Shell.h"

class InfoCommand : public Command
{
  public:
    InfoCommand() : Command{"info", 1, "Shows information about FileSystemObject"}
    {
        CommandRegistry::registerCommand("info", this);
    }

    int operate(Shell &shell, std::vector<std::string> cmd_args) override
    {
        if (cmd_args.size() != 1)
        {
            std::cout << "Bad argument(s). Enter a valid path." << std::endl;
            return -1;
        }

        FileSystemObject *object = objectLocator(shell.getRootDir(), shell.getCurrentDir(), cmd_args.front());

        if (!object)
        {
            return -1;
        }

        object->displayInfo();

        return 0;
    }
};

static InfoCommand infoCommandInstance;
