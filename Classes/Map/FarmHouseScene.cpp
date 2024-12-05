#include "FarmHouseScene.h"

USING_NS_CC;

Scene* FarmHouseScene::createScene() 
{
	return Scene::create();
}

bool FarmHouseScene::init() 
{
	if (!Scene::init()) 
	{
		return false;
	}
	
	//建立地图
	map = TMXTiledMap::create("../Resources/Scenes/FarmYardScene/Farm_room.tmx");
	if (!map)
		CCLOG("Failed to load TMX map");
	map->setPosition(0, 0);
	this->addChild(map, 0, 100);

	return true;
}

void FarmHouseScene::update(float dt) 
{
	Scene::update(dt);
}