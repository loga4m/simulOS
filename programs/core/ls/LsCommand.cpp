#include "LsCommand.h"

#include <iostream>
#include <string>
#include <vector>

#include "../../../cmdunit/CMDunit.h"
#include "../../../filesystem/FileSystem.h"
#include "../../../shell/Shell.h"

LsCommand::LsCommand() : Command("ls", 1, "List directory contents")
{
    CommandRegistry::registerCommand("ls", this);
};

int LsCommand::operate(Shell &shell, std::vector<std::string> command_vec)
{
    LsApp *app = new LsApp();
    int code = app->run(shell, command_vec);
    delete app;
    app = nullptr;
    return code;
}

int LsApp::run(const Shell &shell, std::vector<std::string> command_v)
{
    // Get current directory from shell (assuming shell has this capability)
    DirectoryObject *current_dir = shell.getCurrentDir();
    DirectoryObject *root_dir = shell.getRootDir();

    if (command_v.size() != 1 && command_v.size() != 0)
    {
        std::cout << "Bad argument(s). Enter valid path." << std::endl;
        return -1;
    }

    // Handle path argument if provided
    //
    std::string path = "";
    if (command_v.size() != 0)
    {
        path = command_v.front();
    }

    // Find the target directory
    FileSystemObject *target = objectLocator(root_dir, current_dir, path);

    if (!target)
    {
        return -1; // Error already printed by objectLocator
    }

    if (!target->isDir())
    {
        FileSystemError("Cannot list contents of a file");
        return -1;
    }

    return target->displayContent();
}

static LsCommand lsCommandInstance;
