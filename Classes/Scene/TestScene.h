/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     TestScene.h
 * File Function: ������
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

    // �����¼�����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
    void closeButtonCallback(cocos2d::Ref* sender);  // �˳���ť�Ļص�����
    void update(float dt);  // ���ڸ��� Player ��λ��

    Player* player;  // ��Ҷ���
    // �洢���µļ�
    std::unordered_set<cocos2d::EventKeyboard::KeyCode> keysPressed;
};

#endif // __TEST_SCENE_H__
