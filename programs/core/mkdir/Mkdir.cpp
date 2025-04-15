#include <iostream>
#include <string>
#include <vector>
#include "../../../filesystem/FileSystem.h"
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"


// Author:Elshod Xushvaqtov
// Reviwed: Oyatillo Axadjonov: Comment: Cool!

class MkdirCommand : public Command {
public:
  MkdirCommand() : Command("mkdir", 1, "Creates a new directory") {
    CommandRegistry::registerCommand("mkdir", this);
  }

  int operate(Shell& shell, std::vector<std::string> cmd_args) override {
    if (cmd_args.size() != 1) {
      std::cout << "Error: Bad directory name." << std::endl;
      return -1;
    }

    std::string dir_name = cmd_args.front();
    DirectoryObject* current_dir = shell.getCurrentDir();

    if (current_dir->getChild(dir_name)) {
      std::cout << "Error: Directory already exists." << std::endl;
      return -1;
    }

    DirectoryObject* new_dir = DirectoryObject::create(dir_name, current_dir);
    if (new_dir) {
      std::cout << "Directory '" << dir_name << "' created." << std::endl;
      current_dir->displayContent();
      return 0;
    }
    else {
      FileSystemError("Directory with a bad name");
    }

    return -1;
  }
};

static MkdirCommand mkdirCommandInstance;
