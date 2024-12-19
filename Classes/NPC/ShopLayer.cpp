#include "ShopLayer.h"

USING_NS_CC;

ShopLayer::ShopLayer() 
{

}

ShopLayer* ShopLayer::create() 
{
    ShopLayer* layer = new(std::nothrow) ShopLayer();
    if (layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    else 
    {
        delete layer;
        return nullptr;
    }
}

// 初始化
bool ShopLayer::init() 
{
    if (!Layer::init()) 
    {
        return false;
    }

}

// 设置对话/交易/委托/赠送的NPC
void ShopLayer::setNPC(NPC* npc) 
{
    _currentNPC = npc;
}

// 获取背包物品所在格子
Slot& ShopLayer::getInventorySlots(std::shared_ptr<Item> item)
{
    return Inventory::getInstance()->getSlot(Inventory::getInstance()->findItem(item));
}

// 进行交易 失去PaidItems 得到_ShopItems 返回交易是否成功
bool ShopLayer::tradeItems() 
{
    return 1;
}

// 更新商店内物品及其显示
void ShopLayer::UpdateShopItems() 
{

    Size winSize = Director::getInstance()->getWinSize();

    // 菜单界面 放置购买/交付委托/赠送礼物的button
    
    // 设置剩余金钱数量显示
    auto bullet = Label::create(std::to_string(Inventory::getInstance()->getCoin()), "", 30);
    bullet->setPosition(Vec2(40, 30));
    bullet->setColor(ccc3(0, 0, 0));
    this->addChild(bullet, 3);

    // 显示商店内已有物品
    for (int i = 0; i < _ShopItems.size(); i++)
    {
        // 添加物品图标
        auto item = _ShopItems[i];
        auto itemIcon = Sprite::create(item->image);
        itemIcon->setContentSize(Size(36, 36));
        itemIcon->setPosition(Vec2(50, winSize.height - 50) + Vec2(60, 0) - i * Vec2(0, 60));
        this->addChild(itemIcon, 1, enumToString(item->getType()));
        
        // 添加物品类型
        auto itemName = Label::create(enumToString(item->getType()) + "  $" + std::to_string(item->getprice()) + " last" + std::to_string(_ShopItemsNum[i]), "", 30);
        itemName->setAnchorPoint(Vec2(0, 0.5));
        itemName->setPosition(itemIcon->getPosition() + Vec2(itemIcon->getContentSize().width, 0));
        itemName->setColor(ccc3(0, 0, 0));
        this->addChild(itemName, 1);

        // 添加物品描述
        auto itemDescription = Label::create(item->getDescription(), "", 30);
        itemDescription->setAnchorPoint(Vec2(0, 0.5));
        itemDescription->setPosition(itemName->getPosition() + Vec2(0, itemName->getContentSize().height));
        itemDescription->setColor(ccc3(0, 0, 0));
        this->addChild(itemDescription, 1);

        // 添加购买按钮
        auto itemButton = HoverButton::create("defaulthead.png", "defaulthead.png", "defaulthead.png");
        itemButton->setPosition(itemIcon->getPosition() - Vec2(25, 0));
        itemButton->setContentSize(Size(10, 10));
        itemButton->addTouchEventListener([this,i,bullet](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
            if (!Inventory::getInstance()->isSlotFull() || Inventory::getInstance()->isCoinEnough(_ShopItems[i]->getprice()) || _ShopItemsNum[i] != 0)
            {
                Inventory::getInstance()->changeCoin(0 - _ShopItems[i]->getprice());
                Inventory::getInstance()->addItem(std::shared_ptr<Item>(_ShopItems[i]), 1);
                _ShopItemsNum[i]--;
                bullet->setString(std::to_string(Inventory::getInstance()->getCoin()));
            }

            });
        this->addChild(itemButton, 2);
    }
}

// 向商店中_ShopItems添加物品
void ShopLayer::InsertShopItems(Item* _item, int num)
{
    int _num = 0;// 当前遍历序号
    for (auto search : _ShopItems) 
    {
        if (search == _item) 
        {
            // 已有物品
            _ShopItemsNum[_num] += num;
            return;
        }
        _num++;
    }

    _ShopItems.push_back(_item);
    _ShopItemsNum.push_back(_num);
}

void ShopLayer::DeleteShop() 
{
    this->removeAllChildren();
}