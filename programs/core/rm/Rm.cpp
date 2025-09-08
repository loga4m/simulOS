#include <iostream>
#include <string>
#include <vector>

#include "../../../cmdunit/CMDunit.h"
#include "../../../filesystem/FileSystem.h"
#include "../../../shell/Shell.h"

/*
 *  Author: Elshod Xushvaqtov
 *  Reviewer: Oyatillo Axadjonov
 *  # Approved!
 *
 * */

class RmCommand : public Command
{
  public:
    RmCommand() : Command("rm", 1, "Removes a file")
    {
        CommandRegistry::registerCommand("rm", this);
    }

    int operate(Shell &shell, std::vector<std::string> cmd_args) override
    {
        if (cmd_args.size() != 1)
        {
            std::cout << "Error: Bad arguments(s)." << std::endl;
            return -1;
        }

        std::string file_name = cmd_args.front();
        DirectoryObject *current_dir = shell.getCurrentDir();

        FileSystemObject *file_to_remove = current_dir->getChild(file_name);
        if (!file_to_remove || file_to_remove->isDir())
        {
            std::cout << "Error: File not found." << std::endl;
            return -1;
        }

        file_to_remove->remove();
        file_to_remove = nullptr;
        std::cout << "File '" << file_name << "' removed." << std::endl;
        return 0;
    }
};

static RmCommand rmCommandInstance;
