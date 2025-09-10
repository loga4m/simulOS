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

int LsCommand::operate(Shell &shell, std::vector<std::string> cmd_args)
{
    LsApp *app = new LsApp();
    int code = app->run(shell, cmd_args);
    delete app;
    app = nullptr;
    return code;
}

int LsApp::run(const Shell &shell, std::vector<std::string> cmd_args)
{
    // Get current directory from shell (assuming shell has this capability)
    DirectoryObject *current_dir = shell.getCurrentDir();
    DirectoryObject *root_dir = shell.getRootDir();

    // Handle path argument if provided
    std::string path = "";
    path = cmd_args.front();

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
