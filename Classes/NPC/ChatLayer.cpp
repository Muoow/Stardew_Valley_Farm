/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     ChatLayer.cpp
 * File Function: ChatLayer类的实现
 * Author:        张翔
 * Update Date:   2024/12/16
 ****************************************************************/

#include "ChatLayer.h"
#define backpos "chatlayerbackground2.png"
USING_NS_CC;

ChatLayer::ChatLayer() : currentNPC(nullptr), isStoreOpen(false) {}

ChatLayer::~ChatLayer() {}

bool ChatLayer::init(NPC* npc)
{
    if (!Layer::init()) {
        return false;
    }

    Size winSize = Director::getInstance()->getWinSize();

    currentNPC = npc;

    // 创建menu
    auto menu = Menu::create();
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu, 0, "menu");

    // 创建对话按钮(点击推进对话)
    auto chatButton = MenuItemImage::create(backpos, backpos, CC_CALLBACK_1(ChatLayer::chatButtonCallBack, this));
    chatButton->setScale(0.3);
    chatButton->setPosition(Vec2(winSize.width - chatButton->getBoundingBox().size.width / 2, 3 * chatButton->getBoundingBox().size.height));
    menu->addChild(chatButton,1,"chatButton");
    // 对话按钮的文本
    auto chatButtonContent = Label::create("CHAT", "", 30);
    chatButtonContent->setPosition(chatButton->getPosition());
    chatButtonContent->setColor(ccc3(0, 0, 0));
    this->addChild(chatButtonContent, 2, "chatButtonContent");

    // 创建事件按钮(点击后弹出 买卖东西，制作物品 的界面) 目前不用细做，有个界面背景就行(之后再另分类细做) 但需要点击一次打开，点击第二次关闭
    auto eventButton = MenuItemImage::create(backpos, backpos, CC_CALLBACK_1(ChatLayer::eventButtonCallBack, this));
    eventButton->setScale(0.3);
    eventButton->setPosition(Vec2(winSize.width - eventButton->getBoundingBox().size.width / 2, 2 * eventButton->getBoundingBox().size.height));
    menu->addChild(eventButton,1,"eventButton");
    // 事件按钮的文本
    auto eventButtonContent = Label::create("EVENT", "", 30);
    eventButtonContent->setPosition(eventButton->getPosition());
    eventButtonContent->setColor(ccc3(0, 0, 0));
    this->addChild(eventButtonContent, 2, "eventButtonContent");

    // 创建关闭按钮(退出对话)
    auto quitButton = MenuItemImage::create(backpos, backpos, CC_CALLBACK_1(ChatLayer::quitButtonCallBack, this));
    quitButton->setScale(0.3);
    quitButton->setPosition(Vec2(winSize.width - quitButton->getBoundingBox().size.width / 2, quitButton->getBoundingBox().size.height));
    menu->addChild(quitButton,1,"quitButton");
    // 关闭按钮的文本
    auto quitButtonContent = Label::create("QUIT", "", 30);
    quitButtonContent->setPosition(quitButton->getPosition());
    quitButtonContent->setColor(ccc3(0, 0, 0));
    this->addChild(quitButtonContent, 2, "quitButtonContent");

    // 创建人物头像
    auto profileHead = Sprite::create("defaulthead.png");
    profileHead->setContentSize(Size(3 * quitButton->getBoundingBox().size.height, 3 * quitButton->getBoundingBox().size.height));
    profileHead->setAnchorPoint(Vec2(0, 0));
    profileHead->setPosition(Vec2(0,quitButton->getBoundingBox().size.height / 2));
    this->addChild(profileHead, 1, "profileHead");

    // 创建对话框背景
    auto background = Sprite::create(backpos);
    background->setContentSize(Size(winSize.width- quitButton->getBoundingBox().size.width- profileHead->getBoundingBox().size.width, 3 * quitButton->getBoundingBox().size.height));
    background->setAnchorPoint(Vec2(1, 0));
    background->setPosition(Vec2(winSize.width - quitButton->getBoundingBox().size.width, quitButton->getBoundingBox().size.height / 2));
    this->addChild(background, 0, "background");

    // 创建对话文本标签
    std::string contents = currentNPC->getDialog();
    auto content = Label::create(contents, "", 30);
    content->setAnchorPoint(Vec2(0, 1));
    content->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
    content->setPosition(Vec2(profileHead->getContentSize().width + 10, background->getContentSize().height + quitButton->getBoundingBox().size.height / 2 - 30));
    content->setColor(ccc3(0,0,0));
    this->addChild(content, 1, "content");
    
    // 设置layer属性
    setColor(ccc3(0, 0, 0));
    setOpacity(128);

    return true;
}

ChatLayer* ChatLayer::create(NPC* npc)
{
    ChatLayer* layer = new(std::nothrow) ChatLayer();
    if (layer && layer->init(npc)) 
    {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }
}

void ChatLayer::updateDialog()
{
    currentNPC->advanceDialog();
    auto content1 = dynamic_cast<Label*>(this->getChildByName("content"));
    content1->setString(currentNPC->getDialog());
}

void ChatLayer::closeChat()
{
    currentNPC->jumpToDialog(0);
    this->removeFromParentAndCleanup(true);
}

void ChatLayer::chatButtonCallBack(Ref* pSender)
{
    updateDialog();
}
void ChatLayer::eventButtonCallBack(Ref* pSender)
{
    // 如果事件窗口未打开
    if (!isStoreOpen) 
    {
        isStoreOpen = 1;
        Size winSize = Director::getInstance()->getWinSize();

        // 打开购买/制作界面
        auto storebackground = Sprite::create(backpos);
        storebackground->setContentSize(Size(winSize.width, winSize.height - 3.5 * this->getChildByName("menu")->getChildByName("quitButton")->getBoundingBox().size.height));
        storebackground->setAnchorPoint(Vec2(0, 0));
        storebackground->setPosition(Vec2(0, 3.5 * this->getChildByName("menu")->getChildByName("quitButton")->getBoundingBox().size.height));
        storebackground->setOpacity(128);
        this->addChild(storebackground, 0, "storebackground");
        // 更改事件文本
        auto content1 = dynamic_cast<Label*>(this->getChildByName("eventButtonContent"));
        content1->setString("quitstore");

        // 打开商店
        auto shop = ShopLayer::create();
#if 1
        auto npc = NPC::create("Player/Sandy.png", ALEX);
        this->addChild(npc);
#endif
        shop->setNPC(npc);
        auto item = new Item(CROP, "defaulthead.png", 64, 1);
        shop->InsertShopItems(item, 10);
        shop->UpdateShopItems();
        this->addChild(shop, 3,"shop");

    }
    else 
    {
        isStoreOpen = false;

        // 关闭购买/制作界面
        this->removeChildByName("storebackground");
        auto shop = dynamic_cast<ShopLayer*>(this->getChildByName("shop"));
        shop->DeleteShop();
        this->removeChildByName("shop");
        // 更改事件文本
        auto content1 = dynamic_cast<Label*>(this->getChildByName("eventButtonContent"));
        content1->setString("EVENT");

    }
}
void ChatLayer::quitButtonCallBack(Ref* pSender)
{
    closeChat();
}

