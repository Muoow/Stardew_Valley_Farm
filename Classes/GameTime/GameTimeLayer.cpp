/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     GameTimeLayer.cpp
 * File Function: GameTimeLayer类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "GameTimeLayer.h"
#include "../proj.win32/Constant.h"

USING_NS_CC;

bool GameTimeLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	GameTime::getInstance()->start();

	// 设置时间
	timeLabel = Label::createWithSystemFont(GameTime::getInstance()->toString(), "Arial", 30);
	timeLabel->setColor(ccc3(0, 0, 0));
	timeLabel->setAnchorPoint(Vec2(0,0.5));
	timeLabel->setPosition(Vec2(50, 50)); // 固定图标位置

	// 设置时间显示背景
	timeIcon = Sprite::create("chatlayerbackground2.png");
	timeIcon->setAnchorPoint(Vec2(0, 0.5));
	timeIcon->setContentSize(timeLabel->getContentSize() + Size(0,5));
	timeIcon->setPosition(timeLabel->getPosition());
	this->addChild(timeIcon);

	this->addChild(timeLabel);

	// 每秒更新一次时间
	this->schedule([this](float deltaTime) {
		updateTime(deltaTime);
		}, 1.0f, "update_time_key");

	return true;
}

void GameTimeLayer::updateTime(float delta)
{
	// 更新 timeLabel
	timeLabel->setString(GameTime::getInstance()->toString());
}
