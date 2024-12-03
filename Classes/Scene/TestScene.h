/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     TestScene.h
 * File Function: 测试用
 * Author:        sg
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"
#include "Player/Player.h"
#include <unordered_set>

class TestScene : public cocos2d::Scene {
public:
    TestScene();
    ~TestScene();

    static TestScene* create();
    bool init();

    // 键盘事件处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
    void closeButtonCallback(cocos2d::Ref* sender);  // 退出按钮的回调函数
    void update(float dt);  // 用于更新 Player 的位置

    Player* player;  // 玩家对象
    // 存储按下的键
    std::unordered_set<cocos2d::EventKeyboard::KeyCode> keysPressed;
};

#endif // __TEST_SCENE_H__
