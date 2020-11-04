#ifndef AXISINFO_HPP
#define AXISINFO_HPP    

#include "KeyCode.h"
#include <string>
#include <vector>
	
class AxisKeys
{
public:
	KeyCode positive;
	KeyCode negative;
};	
	
class AxisInfo
{
public:	
	std::string name;
	std::vector<AxisKeys> keys;
//	bool operator== (const AxisInfo& other) const
//	{
//		//code for comparison
//		return (name == other.name);
//	} 	
};

enum AxisDirection
{
	Positive,
	Negative
};

#endif
