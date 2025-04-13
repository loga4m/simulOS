#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <string>
#include "../../../cmdunit/CMDunit.h"


class HistoryCommand : public Command
{
private:
public:
	HistoryCommand();
	int operate(const Shell& shell, std::vector<std::string> command_v) override;
};

class HistoryApp
{
public:
	int run(const Shell& shell, std::vector<std::string> command_v);
};

#endif
