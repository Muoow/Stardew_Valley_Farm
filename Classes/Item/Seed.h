/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Seed.h
 * File Function: Seed类的定义
 * Author:        张翔
 * Update Date:   2024/12/14
 ****************************************************************/

#ifndef _SEED_H_
#define _SEED_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"
#include "Item.h"

class Seed : public Item
{
public:
	// 构造函数
	Seed(const SeedType _seedtype, std::string _image, int _maxstack, int _price);

	const std::string getDescription() override;

	const SeedType& getSubType();


	// 种子
	SeedType seedtype;

};

// 物品类型
const std::shared_ptr<Seed> ITEM_SEED_RADISH_SEED = std::make_shared<Seed>(RADISH_SEED, "Items/RADISH_SEED.png", 200, 1);
const std::shared_ptr<Seed> ITEM_SEED_POTATO_SEED = std::make_shared<Seed>(POTATO_SEED, "Items/POTATO_SEED.png", 200, 1);
const std::shared_ptr<Seed> ITEM_SEED_WHEAT_SEED = std::make_shared<Seed>(WHEAT_SEED, "Items/WHEAT_SEED.png", 200, 1);

#endif // _SEED_H_
