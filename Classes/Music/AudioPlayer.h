/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     AudioPlayer.h
 * File Function: 音频引擎方法的定义
 * Author:        张翔
 * Update Date:   2024/12/8
 ****************************************************************/

#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include "AudioEngine.h"
 // 注 没有找到这四个全局变量的位置 暂时注释掉后用另一个变量代替
 // 音频引擎设置
#if 0
extern int g_backgroundMusicSign;    // 存储当前背景音乐ID
extern int g_soundEffectSign;        // 存储当前音效ID
extern float g_backgroundMusicVolumn;
extern float g_soundEffectVolumn;
#endif
// 音频引擎方法
void audioPlayer(const std::string& audioPath, bool isLoop);

#endif // !_AUDIO_PLAYER_H_