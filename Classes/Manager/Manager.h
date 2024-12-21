/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Manager.h
 * File Function: Manager类的定义
 * Author:        张翔
 * Update Date:   2024/12/19
 ****************************************************************/

#ifndef _MANAGER_
#define _MANAGER_

#include "vector"
#include "cocos2d.h"
#include "FarmObject.h"
#include "FarmLand.h"

class Manager
{
public:
    // 获取单例指针
	static Manager* getInstance();

    // 初始化
    bool init();

    ~Manager();

    // 添加到场景中
    void addToScene(cocos2d::Scene* scene);

    // 从场景中移除
    void removeFromScene(cocos2d::Scene* scene);

    // 添加对象
    void addObject(ObjectType type, float x, float y, cocos2d::Scene* scene);

    // 添加耕地
    void addFarmland(float x, float y, cocos2d::Scene* scene);

    // 根据坐标查找耕地
    FarmLand* findFarmlandByPosition(float x, float y);

    // 根据坐标查找非耕地对象
    FarmObject* findObjectByPosition(float x, float y);

    // 保存游戏状态
    void saveGameState(const std::string& filename);

    // 加载游戏数据
    void loadGameState(const std::string& filename);

    // 更新方法
    void update(cocos2d::Scene* scene);

private:
    std::vector<FarmObject*> objects;     // 非耕地物体
    std::vector<FarmLand*> lands;         // 耕地物体

    // 私有构造函数，禁止外部实例化
    Manager();

    // 禁止拷贝和赋值
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    static Manager* instance;

};

#endif // _MANAGER_
