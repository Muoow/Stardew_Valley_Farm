/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     TestScene.cpp
 * File Function: ������
 * Author:        sg
 * Update Date:   2024/12/3
 ****************************************************************/

#include "TestScene.h"

USING_NS_CC;

TestScene::TestScene() : player(nullptr) {}

TestScene::~TestScene() {}

TestScene* TestScene::create()
{
    TestScene* ret = new TestScene();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CCLOG("Failed to create TestScene!");
    delete ret;
    return nullptr;
}

// ���̰����¼�����
void TestScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    keysPressed.insert(keyCode);  // ��¼���µļ�
}

// �����ͷ��¼�����
void TestScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    keysPressed.erase(keyCode);  // �Ƴ��ɿ��ļ�
}

bool TestScene::init()
{
    // 1. ���ø���ĳ�ʼ��
    if (!Scene::init()) {
        return false;
    }

    // 2. ��������ʾһ����ǩ
    auto label = Label::createWithSystemFont("Test Scene", "consolas", 36);
    label->setPosition(Vec2(400, 300));  // ���ñ�ǩλ��
    this->addChild(label);

    // 3. ��������ʾһ����ť
    auto closeButton = MenuItemFont::create("Close", CC_CALLBACK_1(TestScene::closeButtonCallback, this));
    auto menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    closeButton->setPosition(Vec2(400, 200));  // ���ð�ťλ��
    this->addChild(menu);

    // 4. ��������� Player ����
    player = Player::create("test", "1");  // ���� Player
    if (player == nullptr) {
        CCLOG("Player creation failed!");
        return false;  // �������ʧ�ܣ����� false
    }
    player->setPosition(Vec2(400, 150));  // ���ó�ʼλ��
    this->addChild(player);

    // ���������¼�
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(TestScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(TestScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 5. ÿ֡����һ�Σ����� update
    schedule([this](float dt) {
        this->update(dt);
        }, "update_key");

    return true;
}

// 6. ������ҵ�λ��
void TestScene::update(float dt)
{
    if (player) {
        // ��ʼ��һ����������
        Vec2 direction(0, 0);

        // ���ݰ��µļ����·�������
        if (keysPressed.count(EventKeyboard::KeyCode::KEY_W)) {
            direction.y += 1;  // ����
        }
        if (keysPressed.count(EventKeyboard::KeyCode::KEY_S)) {
            direction.y -= 1;  // ����
        }
        if (keysPressed.count(EventKeyboard::KeyCode::KEY_A)) {
            direction.x -= 1;  // ����
        }
        if (keysPressed.count(EventKeyboard::KeyCode::KEY_D)) {
            direction.x += 1;  // ����
        }

        // ��һ���������������ַ��򲻱䣬����Ϊ1��
        if (direction.length() > 0) {
            direction.normalize();  // ��һ����������
        }

        // �ƶ���ң�����ʸ�������ٶȲ�����ʱ������
        player->setPosition(player->getPosition() + direction * player->getSpeed() * dt);
    }
}

// 7. ��ť����ص��������˳���ǰ����
void TestScene::closeButtonCallback(Ref* sender)
{
    Director::getInstance()->popScene();  // �˳���ǰ�������ص���һ����
}
