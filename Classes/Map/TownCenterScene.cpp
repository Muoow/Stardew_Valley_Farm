/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     TownCenterScene.cpp
 * File Function: TownCenterScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/16
 ****************************************************************/

#include "TownCenterScene.h"
#include "FarmYardScene.h"
#include "../Player/Player.h"
#include "proj.win32/Constant.h"
#include "../GameTime/GameTimeLayer.h"

USING_NS_CC;

Scene* TownCenterScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TownCenterScene::create();
	scene->addChild(layer);
	return scene;
}

bool TownCenterScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	// 创建摄像机
	camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	cocos2d::Vec3 currentPos = camera->getPosition3D();
	currentPos.z = DEFAULT_VIEW_HEIGHT;
	camera->setPosition3D(currentPos);
	this->addChild(camera);

	// 加载瓦片地图
	auto TownCentre = TMXTiledMap::create("Maps/Town.tmx");
	if (!TownCentre) {
		CCLOG("Failed to load tile map");
		return false;
	}
	TownCentre->getLayer("Meta")->setVisible(false);
	TownCentre->setPosition(0, 0);
	TownCentre->setCameraMask(unsigned short(CameraFlag::USER1));
	this->addChild(TownCentre, 0, "TownCentre");

	// 获取地图的基础属性
	auto objectGroup = TownCentre->getObjectGroup("Event");
	if (!objectGroup) {
		CCLOG("Failed to load object layer: Event");
		return false;
	}

	auto spawnPoint = objectGroup->getObject("SpawnPoint");
	auto townToYard = objectGroup->getObject("TownToYard");
	if (spawnPoint.empty() || townToYard.empty()) {
		CCLOG("SpawnPoint not found in Event layer.");
		return false;
	}

	// 创建一个矩形表示 townToYard 区域
	townToYardRect.setRect(townToYard["x"].asFloat(), townToYard["y"].asFloat(), townToYard["width"].asFloat(), townToYard["height"].asFloat());

	auto player = Player::getInstance();
	player->init();
	player->setPosition(spawnPoint["x"].asFloat(), spawnPoint["y"].asFloat());
	player->setCameraMask(unsigned short(CameraFlag::USER1));
	this->addChild(player, 1, "player");

	// 启动每帧更新函数
	this->scheduleUpdate();

	return true;
}

void TownCenterScene::update(float delta)
{
	Player* player = Player::getInstance();

	// 获取 TownCentre 地图对象
	auto TownCentre = (TMXTiledMap*)this->getChildByName("TownCentre");

	// 计算摄像机的位置
	Vec3 currentCameraPos = camera->getPosition3D();

	// 获得玩家的当前位置
	Vec2 currentPosition = player->getPosition();

	// 计算更新后的位置
	Vec2 newPosition = currentPosition + player->getDirection() * player->getSpeed() * delta;

	// 获取玩家目标位置的瓦片GID
	int tileGID = TownCentre->getLayer("Meta")->getTileGIDAt(convertToTileCoords(newPosition));
	if (tileGID) {
		// 获取瓦片属性
		auto properties = TownCentre->getPropertiesForGID(tileGID).asValueMap();
		if (!properties.empty() && properties["Collidable"].asBool()) {
			// 判断瓦片是否具有 "Collidable" 属性且为 true
			// 如果该瓦片不可通行，则直接返回，不更新玩家位置
			return;
		}
	}

	// 更新玩家位置
	player->setPosition(newPosition);

	if (townToYardRect.containsPoint(newPosition)) {
		// 在切换场景之前，先禁用更新
		this->unscheduleUpdate();

		this->removeChild(player);
		player->resetInit();
		Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(SCENE_TRANSITION_DURATION, FarmYardScene::createScene(), cocos2d::Color3B::WHITE));
	}

	// 计算摄像头目标位置
	Vec3 targetCameraPos(newPosition.x, newPosition.y, currentCameraPos.z);
	// 平滑移动摄像机
	camera->setPosition3D(currentCameraPos.lerp(targetCameraPos, 0.1f));// 平滑系数

}

Vec2 TownCenterScene::convertToTileCoords(const Vec2& pos)
{
	// 将玩家的新位置转换为瓦片坐标
	Vec2 tile = Vec2(int(pos.x / MAP_TILE_WIDTH), int((TOWNCENTER_MAP_HEIGHT * MAP_TILE_HEIGHT - pos.y) / MAP_TILE_HEIGHT));

	return tile;
}
