#ifndef ACTIONINFO_HPP
#define ACTIONINFO_HPP

#include "KeyCode.h"
#include <string>
#include <vector>

class ActionInfo
{
public:
	std::string name;
	std::vector<KeyCode> keys;
};

#endif
