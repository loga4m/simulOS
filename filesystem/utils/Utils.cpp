#include "./Utils.h"
#include <set>

bool nameValidator(const std::string &name)
{
    std::set<char> disallowedCharacters = {
        '@', '#', '^', '%', '$', '&', '*',
        '(', ')', '=', '!', '~', '\\', '/',
        '|', '.', ',', '?', '[', ']', ';',
        ':', '`', '"', '\'', ' '
    };
    if (!name.length())
    {
        return false;
    }
    for (int index = 0; index < name.length(); index++)
    {
        if (disallowedCharacters.count(name.at(index)))
        {
            return false;
        }
    }
    return true;
}
