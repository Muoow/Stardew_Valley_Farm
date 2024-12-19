/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Slot.h
 * File Function: Slot类的定义
 * Author:        张翔
 * Update Date:   2024/12/7
 ****************************************************************/
#pragma once
#include <memory>
#include "../Item/Item.h"

class Slot 
{
public:
	// 构造函数
	Slot();

	// 判断是否为空
	bool isEmpty() const;

	// 为空格子添加物品
	void setItem(std::shared_ptr<Item> _item, int _quantity);

	// 删去物品
	void clearSlot();

	// 判断物品是否足够
	bool isQuantityEnough(int amount);

	// 修改物品的数量
	void changeQuantity(int amount);

	// 获取当前物品的种类
	std::shared_ptr<Item> getItem() const;

	// 获取当前物品的数量
	int getQuantity() const;

private:
	std::shared_ptr<Item> item; // 该格子存储的物品
	int quantity;               // 物品数量   

};
