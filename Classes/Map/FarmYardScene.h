/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     FarmYardScene.h
 * File Function: FarmYardScene类的定义
<<<<<<< HEAD
 * Author:        刘逸飞 张翔
=======
 * Author:        张翔
>>>>>>> parent of 1a6d180 (Merge pull request #2 from soyolovealexs/main)
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef _FARM_YARD_SCENE_H_
#define _FARM_YARD_SCENE_H_

#include "cocos2d.h"
#include "Scene/MenuScene.h"
#include "Player/Player.h"


class FarmYardScene : public cocos2d::Scene {
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    // 每一帧被自动调用的 update 方法
    virtual void update(float dt);

    // 实现 FarmYardScene 类的 create 方法
    CREATE_FUNC(FarmYardScene);

    // 获取背景层 未完成
    void getLayerBackground();
private:
    cocos2d::TMXTiledMap* map;
};

#endif // _FARM_YARD_SCENE_H_
