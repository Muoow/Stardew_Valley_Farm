#pragma once
#include "cocos2d.h"
#include "../NPC/ChatLayer.h"
#include "../NPC/NPC.h"
#include "../Item/Item.h"
#include "../proj.win32/Constant.h"
#include "../Inventory/Inventory.h"
#include "../Inventory/InventoryLayer.h"
#include "../Inventory/Slot.h"
#include "../Button/HoverButton.h"
class ShopLayer : public cocos2d::Layer 
{
private:
	NPC* _currentNPC;

	std::vector<Item*> _ShopItems;       // 商店物品/委托奖励
	std::vector<int>   _ShopItemsNum;    // 商店格位数量
	std::vector<Item*> _PaidItems;       // 失去物品/委托物品/赠送物品

	// 将ItemType的枚举转变为字符串
	template <typename T>
	std::string enumToString(T _itemtype) { return "Unknown"; }

public:
	ShopLayer();

	static ShopLayer* create();

	// 初始化
	virtual bool init();

	// 设置对话/交易/委托/赠送的NPC
	void setNPC(NPC* npc);

	// 获取背包物品所在格子
	Slot& getInventorySlots(std::shared_ptr<Item> item);

	// 进行交易 失去PaidItems 得到_ShopItems 返回交易是否成功
	bool tradeItems();

	// 更新商店内物品及其显示
	void UpdateShopItems();

	// 向商店中_ShopItems添加物品
	void InsertShopItems(Item* _item,int num);

	// 清除所有组件
	void DeleteShop();

	template <>
	std::string ShopLayer::enumToString<const ItemType&>(const ItemType& _itemtype)
	{
		switch (_itemtype) {
			case SEED:return "SEED";
			case TOOL:return "TOOL";
			case CROP:return "CROP";
			default:return "something wrong in ItemType";
		}
	}
	template <>
	std::string ShopLayer::enumToString<const ToolType&>(const ToolType& _itemtype)
	{
		switch (_itemtype) {
			case HOE:return "SEED";
			case WATERING_CAN:return "TOOL";
			case PICKAXE:return "CROP";
			case AXE:return "AXE";
			case SCYTHE:return "SCYTHE";
			case FISHING_ROD:return "FISHING_ROD";
			default:return "something wrong in ToolType";
		}
	}
	template <>
	std::string ShopLayer::enumToString<const SeedType&>(const SeedType& _itemtype)
	{
		switch (_itemtype)
		{
			case RADISH_SEED:return "RADISH_SEED";
			case POTATO_SEED:return "POTATO_SEED";
			case WHRAT_SEED:return "WHRAT_SEED";
			default:return "something wrong in SeedType";
		}
	}

};
