/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmLand.cpp
 * File Function: FarmLand类的实现
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#include "FarmLand.h"

USING_NS_CC;

FarmLand::FarmLand(float _x, float _y) :sprite(nullptr), landstate(DRY), obj(nullptr), toRemove(false), dryTime(0), isAddedToScene(false)
{
	sprite = Sprite::create("ImageElements/FarmLand/DrySoil.png");
	if (sprite != nullptr) {
		sprite->setAnchorPoint(Vec2(0, 0));
		sprite->setPosition(_x, _y);
		sprite->setCameraMask(unsigned short(CameraFlag::USER1));
	}
}

FarmLand::~FarmLand() {}

void FarmLand::update()
{
	// 累计干旱时长
	dryTime++;
	// 根据时长判断耕地状态变化
	if (dryTime >= DRY_THRESHOLD) {
		if (landstate == LandState::WET) {
			landstate = LandState::DRY;
			sprite->setTexture("ImageElements/FarmLands/DrySoil.png");
		}
		else if (landstate == LandState::DRY) {
			this->markForRemoval();
			if (obj != nullptr)
				obj->markForRemoval();

		}
	}
}

void FarmLand::watering()
{
	dryTime = 0;
	if (landstate == LandState::DRY) {
		// 将耕地恢复为湿润状态，并重置干旱时间
		landstate = LandState::WET;
		if (sprite != nullptr) {
			sprite->setTexture("ImageElements/FarmLands/WetSoil.png");
		}
	}
}

bool FarmLand::shouldRemove() const
{
	return toRemove;
}

void FarmLand::markForRemoval()
{
	toRemove = true;
}

Sprite* FarmLand::getSprite() const
{
	return sprite;
}

// 获取状态
void FarmLand::setLandState(LandState state)
{
	landstate = state;
}

// 修改状态
LandState FarmLand::getLandState() const
{
	return landstate;
}
