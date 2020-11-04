#ifndef INPUT_HPP
#define INPUT_HPP

#include "KeyCode.h"
#include "Point.h"
#include "ActionInfo.h"
#include "AxisInfo.h"
#include <string>
#include <map>
#include <unordered_map>
#include <vector>

class Input
{
private:
    static std::map<std::string, std::vector<KeyCode>> actionToKeyDictionary;
    static std::map<std::vector<KeyCode>, std::string> keyToActionDictionary;
    static std::map<std::string, AxisInfo> keyToAxisDictionary;
    static std::unordered_map<AxisInfo*, std::string> axisToKeyDictionary;
    static std::vector<KeyCode> keycodes;	
	
public:	
    static void Initialize();
	static void RegisterAxis(AxisInfo axisInfo);
    static bool GetKeyDown(KeyCode keyCode);
    static bool GetKeyUp(KeyCode keyCode);
	static float GetAxis(const std::string& axis);
    static void SetStateUp(KeyCode keyCode, int state);
    static void SetStateDown(KeyCode keyCode, int state);
	static void SetMousePosition(const int& x, const int& y);
	static void SetMouseScrollDirection(const float& direction);
	static Point GetMousePosition();
	static float GetMouseScrollDirection();
};

#endif
