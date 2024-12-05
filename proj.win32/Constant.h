#ifndef _CONSTANT_H_
#define _CONSTANT_H_
#include <string>

constexpr int DESIGN_RESOLUTION_WIDTH = 1280;                             // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;                             // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 960;                               // 小分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                              // 小分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                             // 中分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                             // 中分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                              // 大分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                             // 大分辨率高度
constexpr float FRAME_RATE = 60.0f;                                       // 应用程序帧率
const std::string APPLICATION_TITLE = "星露谷物语 Stardew Valley";       // 应用程序标题

constexpr float SCENE_TRANSITION_DURATION = 0.3f;                         // 场景转换时长

constexpr int MENU_SCENE_BUTTONS_OFFSET_Y = -200;                         // 菜单界面按钮Y轴偏移量
constexpr int MENU_SCENE_NEW_GAME_BUTTON_OFFSET_X = -400;                 // 菜单界面开始按钮X轴偏移量
constexpr int MENU_SCENE_LOAD_GAME_BUTTON_OFFSET_X = 0;                   // 菜单界面载入按钮X轴偏移量
constexpr int MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X = 400;                 // 菜单界面结束按钮X轴偏移量

constexpr float NOMAL_PLAYER_SPEED = 100;                                 // 人物默认移动速度

#endif // _CONSTANT_H_
