#include "Input.h"
#include <iostream>

class KeyState
{
public:
	int down;
	int up;
	KeyState()
	{
		this->down = 0;
		this->up = 0;
	}
};

static std::map<KeyCode, KeyState> keyStates;
Point mousePosition;
float mouseScrollDirection = 0.0f;

std::map<std::string, std::vector<KeyCode>> Input::actionToKeyDictionary;
std::map<std::vector<KeyCode>, std::string> Input::keyToActionDictionary;
std::map<std::string, AxisInfo> Input::keyToAxisDictionary;
std::unordered_map<AxisInfo*, std::string> Input::axisToKeyDictionary;
std::vector<KeyCode> Input::keycodes;	

void Input::Initialize()
{
		mousePosition = {0, 0};
		
		//keyStates[KeyCode::Backspace] = KeyState();
        //keyStates[KeyCode::Delete] = KeyState();
        //keyStates[KeyCode::Tab] = KeyState();
        //Clear = 0,
        //keyStates[KeyCode::Return] = KeyState();
        //keyStates[KeyCode::Pause] = KeyState();
        //keyStates[KeyCode::Escape] = KeyState();
        keyStates[KeyCode::Space] = KeyState();
        //Keypad0 = 0,
        //Keypad1 = 0,
        //Keypad2 = 0,
        //Keypad3 = 0,
        //Keypad4 = 0,
        //Keypad5 = 0,
        //Keypad6 = 0,
        //Keypad7 = 0,
        //Keypad8 = 0,
        //Keypad9 = 0,
        //KeypadPeriod = 0,
        //KeypadDivide = 0,
        //KeypadMultiply = 0,
        //KeypadMinus = 0,
        //KeypadPlus = 0,
        //KeypadEnter = 0,
        //KeypadEquals = 0,
//        keyStates[KeyCode::UpArrow] = KeyState();
//        keyStates[KeyCode::DownArrow] = KeyState();
//        keyStates[KeyCode::RightArrow] = KeyState();
//        keyStates[KeyCode::LeftArrow] = KeyState();
//        keyStates[KeyCode::Insert] = KeyState();
//        keyStates[KeyCode::Home] = KeyState();
//        keyStates[KeyCode::End] = KeyState();
//        keyStates[KeyCode::PageUp] = KeyState();
//        keyStates[KeyCode::PageDown] = KeyState();
        keyStates[KeyCode::F1] = KeyState();
        keyStates[KeyCode::F2] = KeyState();
        keyStates[KeyCode::F3] = KeyState();
        keyStates[KeyCode::F4] = KeyState();
        keyStates[KeyCode::F5] = KeyState();
        keyStates[KeyCode::F6] = KeyState();
        keyStates[KeyCode::F7] = KeyState();
        keyStates[KeyCode::F8] = KeyState();
        keyStates[KeyCode::F9] = KeyState();
        keyStates[KeyCode::F10] = KeyState();
        keyStates[KeyCode::F11] = KeyState();
        keyStates[KeyCode::F12] = KeyState();
        //Alpha0 = 0,
        //Alpha1 = 0,
        //Alpha2 = 0,
        //Alpha3 = 0,
        //Alpha4 = 0,
        //Alpha5 = 0,
        //Alpha6 = 0,
        //Alpha7 = 0,
        //Alpha8 = 0,
        //Alpha9 = 0,
        //Exclaim = 0,
        //DoubleQuote = 0,
        //Hash = 0,
        //Dollar = 0,
        //Ampersand = 0,
        //Quote = 0,
        //LeftParen = 0,
        //RightParen = 0,
        //Asterisk = 0,
        //Plus = 0,
        //Comma = 0,
        //Minus = 0,
        //Period = 0,
        //Slash = 0,
        //Colon = 0,
        //Semicolon = 0,
        //Less = 0,
        //Equals = 0,
        //Greater = 0,
        //Question = 0,
        //At = 0,
        //LeftBracket = 0,
        //Backslash = 0,
        //RightBracket = 0,
        //Caret = 0,
        //Underscore = 0,
        //BackQuote = 0,
        keyStates[KeyCode::A] = KeyState();
		keyStates[KeyCode::B] = KeyState();
		keyStates[KeyCode::C] = KeyState();
		keyStates[KeyCode::D] = KeyState();
		keyStates[KeyCode::E] = KeyState();
		keyStates[KeyCode::F] = KeyState();
		keyStates[KeyCode::G] = KeyState();
		keyStates[KeyCode::H] = KeyState();
		keyStates[KeyCode::I] = KeyState();
		keyStates[KeyCode::J] = KeyState();
		keyStates[KeyCode::K] = KeyState();
		keyStates[KeyCode::L] = KeyState();
		keyStates[KeyCode::M] = KeyState();
		keyStates[KeyCode::N] = KeyState();
		keyStates[KeyCode::O] = KeyState();
		keyStates[KeyCode::P] = KeyState();
		keyStates[KeyCode::Q] = KeyState();
		keyStates[KeyCode::R] = KeyState();
		keyStates[KeyCode::S] = KeyState();
		keyStates[KeyCode::T] = KeyState();
		keyStates[KeyCode::U] = KeyState();
		keyStates[KeyCode::V] = KeyState();
		keyStates[KeyCode::W] = KeyState();
		keyStates[KeyCode::X] = KeyState();
		keyStates[KeyCode::Y] = KeyState();
        keyStates[KeyCode::Z] = KeyState();
        //keyStates[KeyCode::Numlock] = KeyState();
        //keyStates[KeyCode::CapsLock] = KeyState();
        //keyStates[KeyCode::ScrollLock] = KeyState();
        keyStates[KeyCode::LeftShift] = KeyState();
        keyStates[KeyCode::RightShift] = KeyState();        
        keyStates[KeyCode::LeftControl] = KeyState();
        keyStates[KeyCode::RightControl] = KeyState();
        //Alt = 0x12,
        keyStates[KeyCode::LeftAlt] = KeyState();
        keyStates[KeyCode::RightAlt] = KeyState();
        //LeftCommand = 0xFFE9,
        //LeftApple = 0,
        //LeftWindows = 0,
        //RightCommand = 0,
        //RightApple = 0,
        //RightWindows = 0,
        //AltGr = 0,
        //Help = 0,
        //Print = 0,
        //SysReq = 0,
        //Break = 0,
        //Menu = 0,
		keyStates[KeyCode::MouseLeft] = KeyState();
		keyStates[KeyCode::MouseRight] = KeyState();
        keyStates[KeyCode::None] = KeyState();
}

void Input::RegisterAxis(AxisInfo axisInfo)
{	
	if(keyToAxisDictionary.count(axisInfo.name) == 0)
	{
		keyToAxisDictionary[axisInfo.name] = axisInfo;
	}
	if(axisToKeyDictionary.find(&axisInfo) == axisToKeyDictionary.end())
	{
		axisToKeyDictionary[&axisInfo] = axisInfo.name;
	}
}

bool Input::GetKeyDown(KeyCode keyCode)
{
    if(keyStates.count(keyCode) > 0)
    {        
        if (keyStates[keyCode].down == 1)
        {
			//keyStates[keyCode].down = 0;
            return true;
        }   
    }
    return false;
}

bool Input::GetKeyUp(KeyCode keyCode)
{
    if(keyStates.count(keyCode) > 0)
    {        
        if (keyStates[keyCode].up == 1)
        {
			//keyStates[keyCode].up = 0;
            return true;
        }   
    }
    return false;
}

float Input::GetAxis(const std::string& axis)
{
	if(keyToAxisDictionary.count(axis) > 0)
	{
		for (unsigned int i = 0; i < keyToAxisDictionary[axis].keys.size(); i++)
		{
			if (Input::GetKeyDown(keyToAxisDictionary[axis].keys[i].positive))
				return 1.0f;
			else if (Input::GetKeyDown(keyToAxisDictionary[axis].keys[i].negative))
				return -1.0f;
		}
	}

	return 0.0f;
}

void Input::SetStateUp(KeyCode keyCode, int state)
{    
    if(keyStates.count(keyCode) > 0)
    {
		if(keyStates[keyCode].up != state)
			keyStates[keyCode].up = state;
    }
}

void Input::SetStateDown(KeyCode keyCode, int state)
{    
    if(keyStates.count(keyCode) > 0)
    {
		if(keyStates[keyCode].down != state)
			keyStates[keyCode].down = state;
    }
}

void Input::SetMousePosition(const int& x, const int& y)
{
	mousePosition.x = x;
	mousePosition.y = y;
}

void Input::SetMouseScrollDirection(const float& direction)
{
	mouseScrollDirection = direction;
}

Point Input::GetMousePosition()
{
	return mousePosition;
}

float Input::GetMouseScrollDirection()
{
	return mouseScrollDirection;
}
