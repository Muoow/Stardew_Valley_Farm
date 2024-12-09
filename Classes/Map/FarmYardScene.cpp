/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.cpp
 * File Function: FarmYardScene类的实现
 * Author:        张翔
 * Update Date:   2024/12/5
 ****************************************************************/
#include "../Player/Player.h"
#include "FarmYardScene.h"
#include "../Music/AudioPlayer.h"

USING_NS_CC;

// 创建场景
Scene* FarmYardScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FarmYardScene::create();
	scene->addChild(layer);
	return scene;
}

// 初始化场景
bool FarmYardScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	//开启背景音乐
	audioPlayer("Music/backgroundTheme.mp3", 1);

	// 创建摄像机
	_camera = Camera::create();
	_camera->setCameraFlag(CameraFlag::USER1);

	// 设置摄像机的位置
	Vec3 cameraPosition = _camera->getPosition3D();
	// 调低 Z 轴视角，减小 Z 值
	cameraPosition.z -= 100; 
	_camera->setPosition3D(cameraPosition);

	this->addChild(_camera);

	// 加载瓦片地图
	auto FarmYard = TMXTiledMap::create("Maps/FarmYardScene.tmx");
	if (!FarmYard) {
		CCLOG("Failed to load tile map");
		return false;
	}

	this->addChild(FarmYard, 0, "FarmYard");

	FarmYard->setCameraMask(unsigned short(CameraFlag::USER1));

	// 获取地图的基础属性
	auto mapSize = FarmYard->getMapSize();
	auto tileSize = FarmYard->getTileSize();
	auto mapCenter = Vec2(mapSize.width * tileSize.width / 2, mapSize.height * tileSize.height / 2);

	auto objectGroup = FarmYard->getObjectGroup("Event");
	if (!objectGroup) {
		CCLOG("Failed to load object layer: Event");
		return false;
	}

	auto spawnPoint = objectGroup->getObject("SpawnPoint");
	if (spawnPoint.empty()) {
		CCLOG("SpawnPoint not found in Event layer.");
		return false;
	}

	// 提取出生点的 x 和 y 坐标
	float spawnX = spawnPoint["x"].asFloat();
	float spawnY = spawnPoint["y"].asFloat();
	CCLOG("Spawn point coordinates: (%f, %f)", spawnX, spawnY);

	FarmYard->setPosition(0,0);

	auto player = Player::getInstance();

	player->setPosition(spawnX, mapSize.height * tileSize.height - spawnY);

	this->addChild(player);

	player->setCameraMask(unsigned short(CameraFlag::USER1));

	this->scheduleUpdate();

	return true;
}

void FarmYardScene::update(float delta)
{
	Player* player = Player::getInstance();

	// 获得玩家的当前位置方向和速度
	Vec2 _direction = player->getDirection();
	float _speed = player->getSpeed();
	Vec2 currentPosition = player->getPosition();

	// 计算更新后的位置
	Vec2 newPosition = currentPosition + _direction * _speed * delta;

	// 更新玩家位置
	player->setPosition(newPosition);

	// 计算摄像机的位置
	Vec3 currentCameraPos = _camera->getPosition3D();
	Vec3 targetCameraPos(newPosition.x, newPosition.y, currentCameraPos.z);

	// 平滑移动摄像机
	Vec3 smoothedPos = currentCameraPos.lerp(targetCameraPos, 0.1f); // 平滑系数
	_camera->setPosition3D(smoothedPos);
}
