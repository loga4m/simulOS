#include "./Alias.h"
#include "../../../filesystem/utils/Utils.h"
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"
#include <string>
#include <vector>


AliasCommand::AliasCommand()
    : Command{ "alias", 2, "program to give another name to other programs" }
{
    CommandRegistry::registerCommand("alias", this);
}

int AliasCommand::operate(Shell& shell, std::vector<std::string> cmd_args) {
    AliasProgram *program = new AliasProgram();
    int code = program->run(cmd_args);
    delete program;
    program = nullptr;
    return code;
}

int AliasProgram::run(const std::vector<std::string> &cmd_args) {
    const std::string& aliasName = cmd_args.front();

    // Verify this alias name does not exist
    Command* existingAliasCmd = CommandRegistry::getCommand(aliasName);
    if (existingAliasCmd) {
        std::string err_message = "Alias '" + aliasName + "' already exists and ";
        err_message += " is bound to '" + existingAliasCmd->getKey() + "'.";
        CommandError(err_message);
        return -1;
    }
    
    // Featch Command object
    Command* command = CommandRegistry::getCommand(cmd_args.back());

    if (command == nullptr) {
        CommandNotFoundError(cmd_args.back());
        return -1;
    }

    if (!nameValidator(aliasName)) {
        CommandError("Bad alias name.");
        return -1;
    }
    
    CommandRegistry::registerCommand(aliasName, command);
    return 0;
}

static AliasCommand AliasCommndInstance;
