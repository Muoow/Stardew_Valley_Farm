/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Inventory.h
 * File Function: Inventory类的定义
 * Author:        张翔
 * Update Date:   2024/12/7
 ****************************************************************/

#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "../Item/Item.h"
#include "Slot.h"
#include "cocos2d.h" 

class Inventory
{
public:
	// 获取单例
	static Inventory* getInstance();

	// 禁止拷贝和赋值
	Inventory(const Inventory&) = delete;
	Inventory& operator=(const Inventory&) = delete;

	// 初始化背包，设置槽位数
	void init(int slotCount);

	// 检索背包中某件物品的位置
	int findItem(std::shared_ptr<Item> item);

	// 获取背包槽位
	Slot& getSlot(int index);

	// 获取背包当前已经装了多少东西
	int getTotalItemCount() const;

	// 修改当前手持物
	void changeCurrHeldItem(int change);

	// 添加物品到背包
	void addItem(std::shared_ptr<Item> item, int quantity);

	// 判断物品是否足够
	bool isItemEnough(std::shared_ptr<Item> item, int quantity);

	// 判断槽位是否已满
	bool isSlotFull();

	// 修改物品数量
	void changeItemQuantity(std::shared_ptr<Item> item, int quantity);

	// 交换槽位中的物品
	bool swapItems(int index1, int index2);

	// 判断金钱是否足够
	bool isCoinEnough(int price);

	// 获取当前金钱数量
	int getCoin();

	// 修改金币数量
	void changeCoin(int amount);

private:
	Inventory();

	// 单例指针
	static Inventory* instance;

	// 存储多个槽位
	std::vector<Slot> slots;

	// 金币数量
	int coin;

	// 当前手持物索引
	int currentHeldItemIndex; 

};

#endif // _INVENTORY_H_