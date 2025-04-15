#include <iostream>
#include <string>
#include <vector>
#include "../../../filesystem/FileSystem.h"
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"

/*
 *  Author: Exshod Xushvaqtov
 *  Reviewer: Oyatillo Axadjonov
 *  # Approved!
 *
 * */

class RmfCommand : public Command {
public:
    RmfCommand() : Command("rmf", 1, "Removes a directory") {
	CommandRegistry::registerCommand("rmf", this);
    }

    int operate(Shell& shell, std::vector<std::string> cmd_args) override {
        if (cmd_args.size() != 1) {
            std::cout << "Error: Bad argument(s).." << std::endl;
            return -1;
        }

        std::string dir_name = cmd_args.front();
        DirectoryObject* current_dir = shell.getCurrentDir();

        FileSystemObject* dir_to_remove = current_dir->getChild(dir_name);
        if (!dir_to_remove || !dir_to_remove->isDir()) {
            std::cout << "Error: Directory not found." << std::endl;
            return -1;
        }


        dir_to_remove->remove();
        std::cout << "Directory '" << dir_name << "' removed." << std::endl;
        return 0;
    }
};


static RmfCommand rmfCommandInstance;
