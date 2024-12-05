#include "FarmYardScene.h"

USING_NS_CC;

Scene* FarmYardScene::createScene() 
{
	return FarmYardScene::create();
}

bool FarmYardScene::init() 
{
	if (!Scene::init()) 
	{
		return false;
	}

	//建立地图
	map = TMXTiledMap::create("../Resources/Scenes/FarmYardScene/Farm_map_simple.tmx");
	if (!map)
		CCLOG("Failed to load TMX map");
	map->setPosition(0, 0);
	this->addChild(map, 0, 100);

	return true;
}

void FarmYardScene::update(float dt)
{
	//调用Scene继承Node的update 
	Scene::update(dt);
}
void FarmYardScene::getLayerBackground()
{
	auto layer = map->getLayer("Background");
}