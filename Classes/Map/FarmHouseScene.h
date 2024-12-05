/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmHouseScene.h
 * File Function: FarmHouseScene类的定义
 * Author:        张翔
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef _FARM_HOUSE_SCENE_H_
#define _FARM_HOUSE_SCENE_H_

#include "cocos2d.h"

class FarmHouseScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 每一帧被自动调用的 update 方法
    virtual void update(float dt);

    // 实现 FarmHouseScene 类的 create 方法
    CREATE_FUNC(FarmHouseScene);



private:
    cocos2d::TMXTiledMap* map;
};

#endif // _FARM_HOUSE_SCENE_H_
