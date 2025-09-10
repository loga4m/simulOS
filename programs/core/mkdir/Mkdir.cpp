#include <iostream>
#include <string>
#include <vector>

#include "../../../cmdunit/CMDunit.h"
#include "../../../filesystem/FileSystem.h"
#include "../../../shell/Shell.h"

// Author:Elshod Xushvaqtov
// Reviwed: Oyatillo Axadjonov: Comment: Cool!

class MkdirCommand : public Command
{
  public:
    MkdirCommand() : Command("mkdir", 1, "Creates a new directory")
    {
        CommandRegistry::registerCommand("mkdir", this);
    }

    int operate(Shell &shell, std::vector<std::string> cmd_args) override
    {
        std::string dir_name = cmd_args.front();
        DirectoryObject *current_dir = shell.getCurrentDir();
        FileSystemObject *look_up_obj = current_dir->getChild(dir_name);
        if (look_up_obj)
        {
            std::cout << "Error: FileSystemObject with this name already exists." << std::endl;
            return -1;
        }

        DirectoryObject *new_dir = DirectoryObject::create(dir_name, current_dir);
        if (new_dir)
        {
            std::cout << "Directory '" << dir_name << "' created." << std::endl;
            return 0;
        }
        else
        {
            FileSystemError("Directory with a bad name");
        }

        return -1;
    }
};

static MkdirCommand mkdirCommandInstance;
