#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <string>

class Shell;
#include "../../../cmdunit/CMDunit.h"


class HistoryCommand : public Command
{
public:
	HistoryCommand();
	int operate(const Shell& shell, std::vector<std::string> args) override;
};

class HistoryApp
{
public:
	int run(const Shell& shell, std::vector<std::string> command_v);
};

#endif
