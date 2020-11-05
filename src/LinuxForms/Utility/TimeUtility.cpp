#include "TimeUtility.h"
#include <sstream>
#include <iomanip>

double TimeUtility::deltaTime = 0.0f;
double TimeUtility::time = 0.0f;
TimePoint TimeUtility::tp1;
TimePoint TimeUtility::tp2;

void TimeUtility::Initialize()
{
    TimeUtility::deltaTime = 0.0f;
    TimeUtility::time = 0.0f;

    tp1 = std::chrono::system_clock::now();
    tp2 = std::chrono::system_clock::now();
}

void TimeUtility::Update()
{
    tp2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = tp2 - tp1;
    tp1 = tp2;

    TimeUtility::SetDeltaTime(elapsedTime.count());
}

void TimeUtility::SetDeltaTime(double dt)
{
    if(TimeUtility::time >= 1000000)
		TimeUtility::time = 0.0;

	TimeUtility::deltaTime = dt;
	TimeUtility::time += dt;
}

double TimeUtility::GetDeltaTime()
{
    return TimeUtility::deltaTime;
}

double TimeUtility::GetTime()
{
    return TimeUtility::time;
}

std::string TimeUtility::GetDateTime()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    std::string timestring = oss.str();

    return timestring;
}