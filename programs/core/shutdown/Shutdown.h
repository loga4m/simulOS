#ifndef SHUTDOWN_H
#define SHUTDOWN_h

#include <string>
#include <vector>

class Shell;
#include "../../../cmdunit/CMDunit.h"

class ShutdownCommand : public Command
{
public:
	ShutdownCommand();
	int operate(Shell& shell, std::vector<std::string> cmd_args) override;
};


#endif
