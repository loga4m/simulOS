#ifndef SHUTDOWN_H
#define SHUTDOWN_h
#include <string>
#include <vector>
#include "../../../cmdunit/CMDunit.h"

class ShutdownCommand : public Command
{
private:
public:
	ShutdownCommand();
	int operate(const Shell& shell, std::vector<std::string> command_vec) override;
};


#endif
