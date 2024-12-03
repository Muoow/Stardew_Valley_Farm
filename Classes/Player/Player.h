/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Player.h
 * File Function: Player类的定义
 * Author:        张翔
 * Update Date:   2024/12/3
 ****************************************************************/

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Bag.h"
#include "SkillTree.h"
#include "cocos2d.h"

class Player : public cocos2d::Sprite {
public:
	Player();
	~Player();

	// 创建 Player 对象
	static Player* create(const std::string name, const std::string spriteFile);

	// 获取经验值
	int getExperience() const { return experience; }

	// 增加经验值
	void gainExperience(int exp);

	// 获取金钱
	int getMoney() const { return money; }

	// 修改金钱
	void addMoney(int amount);
	bool spendMoney(int amount);

	// 获取背包
	// Bag& getBag() { return bag; }

	// 获取技能树
	// SkillTree& getSkillTree() { return skillTree; }

	// 移动函数
	void move(float dx, float dy);

	float getSpeed() const { return speed; };

private:

	std::string name;       // 玩家名字
	int experience;         // 玩家经验值
	int money;              // 玩家金钱
	// Bag bag;                // 玩家背包
	// SkillTree skillTree;    // 玩家技能树
	float speed;

};

#endif // _PLAYER_H_
