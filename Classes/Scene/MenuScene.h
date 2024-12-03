#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
    // 创建场景
    static cocos2d::Scene* createScene();

    // 初始化场景
    virtual bool init();

    //----------------------testscene----------------------
    // 切换到 TestScene 的回调函数
    void goToTestScene(cocos2d::Ref* sender);
    //----------------------testscene----------------------

    // 实现 MenuScene 类的 create 方法
    CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
