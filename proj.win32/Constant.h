/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Constant.h
 * File Function: 常变量的定义
 * Author:        张翔
 * Update Date:   2024/12/11
 ****************************************************************/

#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include <string>
#include <vector>

constexpr int DESIGN_RESOLUTION_WIDTH = 1280;												 // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;												 // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 960;													 // 小分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 540;											     // 小分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                                                // 中分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                                                // 中分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                                 // 大分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                                                // 大分辨率高度
constexpr float FRAME_RATE = 60.0f;                                                          // 应用程序帧率
const std::string APPLICATION_TITLE = "星露谷物语 Stardew Valley";                           // 应用程序标题

constexpr float SCENE_TRANSITION_DURATION = 0.3f;                                            // 场景转换时长

constexpr int MENU_SCENE_BUTTONS_OFFSET_Y = -200;                                            // 菜单界面按钮Y轴偏移量
constexpr int MENU_SCENE_NEW_GAME_BUTTON_OFFSET_X = -400;                                    // 菜单界面开始按钮X轴偏移量
constexpr int MENU_SCENE_LOAD_GAME_BUTTON_OFFSET_X = 0;                                      // 菜单界面载入按钮X轴偏移量
constexpr int MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X = 400;                                    // 菜单界面结束按钮X轴偏移量

constexpr int DEFAULT_MUSIC_SIGN = -1;                                                       // 缺省音乐标识
constexpr float DEFAULT_MUSIC_VOLUMN = 0.5f;                                                 // 缺省音量大小

constexpr float NOMAL_PLAYER_SPEED = 100;                                                    // 人物默认移动速度
constexpr int PLAYER_IMAGE_WIDTH = 64;                                                       // 人物移动图集宽度
constexpr int PLAYER_IMAGE_HEIGHT = 128;                                                     // 人物移动图集高度
constexpr int PLAYER_FRAME_RATE = 4;                                                         // 人物移动帧数
constexpr int PLAYER_DIRECTION_NUM = 4;                                                      // 人物可移动方向数
constexpr int PLAYER_FRAME_WIDTH = PLAYER_IMAGE_WIDTH / PLAYER_FRAME_RATE;                   // 每帧宽度（图片宽度/帧数）
constexpr int PLAYER_FRAME_HEIGHT = PLAYER_IMAGE_HEIGHT / PLAYER_DIRECTION_NUM;              // 每帧高度（图片高度/行数）
constexpr float PLAYER_FRAME_DELAY = 0.1f;                                                   // 每帧动画延迟

constexpr int DEFAULT_VIEW_HEIGHT = 400;                                                     // 默认视角高度
constexpr int MAX_VIEW_HEIGHT = 500;                                                         // 地图中最大视角高度
constexpr int MIN_VIEW_HEIGHT = 200;                                                         // 地图中最小视角高度

constexpr int MAP_TILE_WIDTH = 16;                                                           // 地图瓦片宽度
constexpr int MAP_TILE_HEIGHT = 16;                                                          // 地图瓦片高度 
constexpr int FARMYARD_MAP_WIDTH = 100;                                                      // FarmYard地图宽度
constexpr int FARMYARD_MAP_HEIGHT = 80;                                                      // FarmYard地图高度
constexpr int FARMHOUSE_MAP_WIDTH = 14;                                                      // FarmHouse地图宽度
constexpr int FARMHOUSE_MAP_HEIGHT = 14;                                                     // FarmHouse地图高度
constexpr int TOWNCENTER_MAP_WIDTH = 60;                                                     // TownCenter地图宽度
constexpr int TOWNCENTER_MAP_HEIGHT = 50;                                                    // TownCenter地图高度

constexpr int TIME_DIPLAY_OFFSET_X = -300;                                                   // 时间显示背景X轴偏移量
constexpr int TIME_DIPLAY_OFFSET_Y = -50;                                                    // 时间显示背景Y轴偏移量

constexpr int DEFAULT_CAPACITY = 30;                                                         // 默认背包容量
constexpr int DEFAULT_BAR = 10;                                                              // 默认物品栏容量

// 物品种类枚举
enum ItemType 
{
	SEED,          // 种子
	TOOL,          // 工具
 	OTHER,         // 其他 
};

// 每种物品的具体描述
const std::string SEED_DESCRIPTION = " ";
const std::string TOOL_DESCRIPTION = " ";
const std::string OTHER_DESCRIPTION = " ";

// 工具类型枚举
enum ToolType 
{
    HOE,           // 锄头
    WATERING_CAN,  // 浇水壶
    PICKAXE,       // 镐子
    AXE,           // 斧头
    SCYTHE,        // 镰刀
    FISHING_ROD,   // 钓鱼竿
};

// 每种功能的具体描述
const std::string TOOL_HOE_DESCRIPTION = " ";
const std::string TOOL_WATERING_CAN_DESCRIPTION = " ";
const std::string TOOL_PICKAXE_DESCRIPTION = " ";
const std::string TOOL_AXE_DESCRIPTION = " ";
const std::string TOOL_SCYTHE_DESCRIPTION = " ";
const std::string TOOL_FISHING_ROD_DESCRIPTION = " ";

// 种子类型枚举
enum SeedType 
{
    RADISH_SEED,
    POTATO_SEED,
    WHEAT_SEED,
};

// 每种种子的具体描述
const std::string SEED_RADISH_DESCRIPTION = " ";
const std::string SEED_POTATO_DESCRIPTION = " ";
const std::string SEED_WHEAT_DESCRIPTION = " ";

// 商店操作类型枚举
enum ShopType
{
    SHOP_BUY,      // 购买物品
    SHOP_SELL,     // 卖出物品
    TASK_REWARD,   // 委托奖励
    TASK_PAID,     // 委托所需
    PRESENT,       // 赠送
};

enum ObjectType
{
    TREE,
    WEED,
    STONE,
    CROP,
};

constexpr int OBJECT_TREE_WIDTH = 16;
constexpr int OBJECT_TREE_HEIGHT = 16;
constexpr int OBJECT_WEED_WIDTH = 16;
constexpr int OBJECT_WEED_HEIGHT = 16;
constexpr int OBJECT_STONE_WIDTH = 16;
constexpr int OBJECT_STONE_HEIGHT = 16;
constexpr int OBJECT_CROP_WIDTH = 16;
constexpr int OBJECT_CROP_HEIGHT = 16;



enum LandState
{
    DRY, 
    WET,
};

constexpr int DRY_THRESHOLD = 10;

// NPC的种类
enum NPCType
{
    ALEX,
    ABIGAIL,
    CAROLINE,
    LEWIS,
};

const std::vector<std::string> NPC_ALEX_DIALOG = {
    " 1",
    " 2",
    " 3",
};

const std::vector<std::string> NPC_ABIGAIL_DIALOG = {
    " ",
    " ",
    " ",
};

const std::vector<std::string> NPC_CAROLINE_DIALOG = {
    " ",
    " ",
    " ",
};

const std::vector<std::string> NPC_LEWIS_DIALOG = {
    " ",
    " ",
    " ",
};

#endif // _CONSTANT_H_
