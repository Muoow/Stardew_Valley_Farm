/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     GameTime.cpp
 * File Function: GameTime类的实现
 * Author:        张翔
 * Update Date:   2024/12/13
 ****************************************************************/

#include "GameTime.h"
#include "cocos2d.h"

 // 静态实例初始化
GameTime* GameTime::instance = nullptr;

 // 获取单例实例
GameTime* GameTime::getInstance()
{
	if (instance == nullptr) {
		// 使用 nothrow 分配内存
		instance = new (std::nothrow) GameTime();
		// 初始化失败则销毁实例
		if (!instance) {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

GameTime::GameTime(int y, int m, int d, int h, int min, double speed) :year(y), month(m), day(d), hour(h), minute(min), timeSpeed(speed), running(false)
{
	normalize();
}

void GameTime::normalize()
{
	if (minute >= 60)
	{
		minute = 0;
		hour++;
		if (hour >= 24) 
		{
			hour = 0;
			day++;
			if (day > 30) 
			{
				day = 1;
				month++;
				if (month > 4) 
				{
					month = 1;
					year++;
				}
			}
		}
	}
	// 如果时间有错就重新更新
	if (minute >= 60 || hour >= 24 || day > 30 || month > 4) 
	{
		GameTime::normalize();
	}
}

void GameTime::updateLoop()
{
	while (running) {
		// 更新间隔
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		// 添加时间
		addSeconds(1); 
	}
}

void GameTime::setTimeSpeed(double speed)
{
	timeSpeed = speed;
}

void GameTime::start()
{
	running = true;
	std::thread(&GameTime::updateLoop, this).detach();
}

void GameTime::stop()
{
	running = false;
}

void GameTime::addSeconds(int realMinutes)
{
	int gameMinutes = static_cast<int>(realMinutes * timeSpeed);
	minute += gameMinutes;
	normalize();
}

std::string GameTime::toString() const
{
	std::string _time = std::to_string(year);
	_time += " ";
	_time += (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
	_time += " ";
	_time += (day < 10) ? "0" + std::to_string(day) : std::to_string(day);
	_time += " ";
	_time += (hour < 10) ? "0" + std::to_string(hour) : std::to_string(hour);
	_time += " ";
	_time += (minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute);
	return _time;
}

std::string GameTime::judgeTime()
{
	if (hour >= 6 && hour < 18) 
	{
		return "day";
	}
	else if (hour>=18) 
	{
		return "night";
	}
	else 
	{
		return "midnight";
	}
}

void GameTime::setnextday() 
{
	minute = 0;
	hour = 6;
	day++;
}