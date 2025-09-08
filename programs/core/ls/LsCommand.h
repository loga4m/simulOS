#ifndef LS_H
#define LS_H

#include <string>
#include <vector>

#include "../../../cmdunit/CMDunit.h"

class Shell;

class LsCommand : public Command
{
  private:
  public:
    LsCommand();
    int operate(Shell &shell, std::vector<std::string> command_v) override;
};

class LsApp
{
  public:
    int run(const Shell &shell, std::vector<std::string> command_v);
};

#endif
