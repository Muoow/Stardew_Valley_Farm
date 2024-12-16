/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     GameTime.h
 * File Function: GameTime类的定义
 * Author:        张翔
 * Update Date:   2024/12/13
 ****************************************************************/

#ifndef _GAME_TIME_H_
#define _GAME_TIME_H_

#include <chrono>
#include <thread>
#include <mutex>

class GameTime 
{
private:
	// 静态实例指针
	static GameTime* instance; 

	// 年月日
	int year, month, day;
	// 
	int hour, minute;
	// 时间流动速度
	double timeSpeed;
	// 控制是否更新时间
	bool running;     

	// 构造函数
	GameTime(int y = 1, int m = 1, int d = 1, int h = 6, int min = 0, double speed = 1.0);
	// 规范化时间和日期
	void normalize();
	// 自动更新线程
	void updateLoop();

public:
	// 禁止拷贝和赋值操作
	GameTime(const GameTime&) = delete;
	GameTime& operator=(const GameTime&) = delete;

	// 获取单例实例
	static GameTime* getInstance();

	// 设置时间流速
	void setTimeSpeed(double speed);

	// 控制线程
	void start();
	void stop();

	// 添加时间
	void addSeconds(int realSeconds);

	// 以字符串形式获取时间信息
	std::string toString() const;

	// 判断当前时间
	std::string judgeTime();

	// 到达下一天
	void setnextday();
};

#endif // _GAME_TIME_H_
