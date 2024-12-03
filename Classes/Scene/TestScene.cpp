/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     TestScene.cpp
 * File Function: 测试用
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

// 键盘按下事件处理
void TestScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	keysPressed.insert(keyCode);  // 记录按下的键
}

// 键盘释放事件处理
void TestScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	keysPressed.erase(keyCode);  // 移除松开的键
}

bool TestScene::init()
{
	// 1. 调用父类的初始化
	if (!Scene::init()) {
		return false;
	}

	// 2. 创建并显示一个标签
	auto label = Label::createWithSystemFont("Test Scene 测试", "consolas", 36);
	label->setPosition(Vec2(400, 300));  // 设置标签位置
	this->addChild(label);

	// 3. 创建并显示一个按钮
	auto closeButton = MenuItemFont::create("Close", CC_CALLBACK_1(TestScene::closeButtonCallback, this));
	auto menu = Menu::create(closeButton, nullptr);
	menu->setPosition(Vec2::ZERO);
	closeButton->setPosition(Vec2(400, 200));  // 设置按钮位置
	this->addChild(menu);

	// 4. 创建并添加 Player 对象
	player = Player::create("test", "1");  // 创建 Player
	if (player == nullptr) {
		CCLOG("Player creation failed!");
		return false;  // 如果创建失败，返回 false
	}
	player->setPosition(Vec2(400, 150));  // 设置初始位置
	this->addChild(player);

	// 监听键盘事件
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(TestScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(TestScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// 5. 每帧更新一次，调用 update
	schedule([this](float dt) {
		this->update(dt);
		}, "update_key");

	return true;
}

// 6. 更新玩家的位置
void TestScene::update(float dt)
{
	if (player) {
		// 初始化一个方向向量
		Vec2 direction(0, 0);

		// 根据按下的键更新方向向量
		if (keysPressed.count(EventKeyboard::KeyCode::KEY_W)) {
			direction.y += 1;  // 向上
		}
		if (keysPressed.count(EventKeyboard::KeyCode::KEY_S)) {
			direction.y -= 1;  // 向下
		}
		if (keysPressed.count(EventKeyboard::KeyCode::KEY_A)) {
			direction.x -= 1;  // 向左
		}
		if (keysPressed.count(EventKeyboard::KeyCode::KEY_D)) {
			direction.x += 1;  // 向右
		}

		// 归一化方向向量（保持方向不变，长度为1）
		if (direction.length() > 0) {
			direction.normalize();  // 归一化方向向量
		}

		// 移动玩家，方向矢量乘以速度并乘以时间增量
		player->setPosition(player->getPosition() + direction * player->getSpeed() * dt);
	}
}

// 7. 按钮点击回调函数，退出当前场景
void TestScene::closeButtonCallback(Ref* sender)
{
	Director::getInstance()->popScene();  // 退出当前场景，回到上一场景
}
