/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmHouseScene.cpp
 * File Function: FarmHouseScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/16
 ****************************************************************/

#include "FarmHouseScene.h"
#include "FarmYardScene.h"
#include "../Player/Player.h"
#include "proj.win32/Constant.h"
#include "../GameTime/GameTimeLayer.h"

USING_NS_CC;

Scene* FarmHouseScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FarmHouseScene::create();
	scene->addChild(layer);
	return scene;
}

bool FarmHouseScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	// 设置默认摄像头位置
	camera= Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	cocos2d::Vec3 currentPos = camera->getPosition3D();
	currentPos.x = FARMHOUSE_MAP_WIDTH * MAP_TILE_WIDTH / 2;
	currentPos.y = FARMHOUSE_MAP_HEIGHT * MAP_TILE_HEIGHT / 2;
	currentPos.z = MIN_VIEW_HEIGHT;
	camera->setPosition3D(currentPos);
	this->addChild(camera);

	// 加载瓦片地图
	auto FarmHouse = TMXTiledMap::create("Maps/FarmHouseScene.tmx");
	if (!FarmHouse) {
		CCLOG("Failed to load tile map");
		return false;
	}
	FarmHouse->getLayer("Meta")->setVisible(false);
	FarmHouse->setPosition(0, 0);
	FarmHouse->setCameraMask(unsigned short(CameraFlag::USER1));
	this->addChild(FarmHouse, 0, "FarmHouse");

	// 获取地图的基础属性
	auto objectGroup = FarmHouse->getObjectGroup("Event");
	if (!objectGroup) {
		CCLOG("Failed to load object layer: Event");
		return false;
	}

	auto spawnPoint = objectGroup->getObject("SpawnPoint");
	auto houseToYard = objectGroup->getObject("HouseToYard");
	if (spawnPoint.empty()|| houseToYard.empty()) {
		CCLOG("SpawnPoint not found in Event layer.");
		return false;
	}

	// 创建一个矩形表示 houseToYard 区域
	houseToYardRect.setRect(houseToYard["x"].asFloat(), houseToYard["y"].asFloat(), houseToYard["width"].asFloat(), houseToYard["height"].asFloat());

	// 创建玩家
	auto player = Player::getInstance();
	player->init();
	player->setPosition(spawnPoint["x"].asFloat(), spawnPoint["y"].asFloat());
	player->setCameraMask(unsigned short(CameraFlag::USER1));
	this->addChild(player, 1, "player");

	// 启动每帧更新函数
	this->scheduleUpdate();

	return true;
}

void FarmHouseScene::update(float delta)
{
	Player* player = Player::getInstance();

	// 获取 FarmHouse 地图对象
	auto FarmHouse = (TMXTiledMap*)this->getChildByName("FarmHouse");

	// 获得玩家的当前位置
	Vec2 currentPosition = player->getPosition();

	// 计算更新后的位置
	Vec2 newPosition = currentPosition + player->getDirection() * player->getSpeed() * delta;

	// 获取玩家目标位置的瓦片GID
	int tileGID = FarmHouse->getLayer("Meta")->getTileGIDAt(convertToTileCoords(newPosition));
	if (tileGID) {
		// 获取瓦片属性
		auto properties = FarmHouse->getPropertiesForGID(tileGID).asValueMap();
		if (!properties.empty()&& properties["Collidable"].asBool()) {
			// 判断瓦片是否具有 "Collidable" 属性且为 true
		    // 如果该瓦片不可通行，则直接返回，不更新玩家位置
			return;
		}
	}

	// 更新玩家位置
	player->setPosition(newPosition);

	if (houseToYardRect.containsPoint(newPosition)) {
		// 在切换场景之前，先禁用更新
		this->unscheduleUpdate();

		this->removeChild(player);
		player->resetInit();
		Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, FarmYardScene::createScene(), cocos2d::Color3B::WHITE));
	}

}

Vec2 FarmHouseScene::convertToTileCoords(const Vec2& pos)
{
	// 将玩家的新位置转换为瓦片坐标
	Vec2 tile = Vec2(int(pos.x / MAP_TILE_WIDTH), int((FARMHOUSE_MAP_HEIGHT * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

	return tile;
}
