#ifndef TIMEUTILITY_HPP
#define TIMEUTILITY_HPP

#include <chrono>
#include <string>

typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;

class TimeUtility
{
public:
    static void Initialize();
	static void Update();
    static double GetDeltaTime();
    static double GetTime();
    static std::string GetDateTime();
private:
	static double deltaTime;
	static double time;
    static void SetDeltaTime(double dt);
    static TimePoint tp1;
    static TimePoint tp2;
};

#endif