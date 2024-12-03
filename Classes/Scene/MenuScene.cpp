#include "MenuScene.h"
#include "Button/HoverButton.h"
#include "TestScene.h"

USING_NS_CC;

// 创建场景
Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

// 初始化场景
bool MenuScene::init()
{
    // 创建场景
    if (!Scene::init()){
        return false;
    }

    // 加载背景
    const auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
    const auto background = Sprite::create("../Resources/Scenes/MenuScene.png");
    background->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    this->addChild(background);

    //----------------------testscene----------------------
    // 创建一个菜单项（按钮），点击后切换到 TestScene
    auto goToTestItem = MenuItemFont::create("Go to Test Scene", CC_CALLBACK_1(MenuScene::goToTestScene, this));

    // 创建菜单并添加菜单项
    auto menu = Menu::create(goToTestItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    goToTestItem->setPosition(Vec2(400, 300));  // 按钮的位置

    // 将菜单添加到场景中
    this->addChild(menu);
    //----------------------testscene----------------------

    // 创建按钮
    auto newGameButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/CreateButton.png",
        "../Resources/Buttons/MenuSceneButtons/CreateButton.png",
        "../Resources/Buttons/MenuSceneButtons/CreateButton.png");
    auto loadGameButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/ExitButton.png",
        "../Resources/Buttons/MenuSceneButtons/ExitButton.png",
        "../Resources/Buttons/MenuSceneButtons/ExitButton.png");
    auto exitGameButton = HoverButton::create("../Resources/Buttons/MenuSceneButtons/LoadButton.png",
        "../Resources/Buttons/MenuSceneButtons/LoadButton.png",
        "../Resources/Buttons/MenuSceneButtons/LoadButton.png");



    this->addChild(newGameButton);
    this->addChild(loadGameButton);
    this->addChild(exitGameButton);

    return true;
}

// 回调函数，点击按钮后切换到 TestScene
void MenuScene::goToTestScene(cocos2d::Ref* sender)
{
    // 使用 replaceScene 切换到 TestScene
    Director::getInstance()->replaceScene(TestScene::create());
}
