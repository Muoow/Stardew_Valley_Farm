/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     AudioPlayer.cpp
 * File Function: 音频引擎方法的实现
 * Author:        
 * Update Date:   2024/12/8
 ****************************************************************/
#include "AudioPlayer.h"
// 临时用作全局变量 待.H文件中全局变量有定义了再删除
#if 1
int g_backgroundMusicSign1 = cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID;
int g_soundEffectSign1 = cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID;
float g_backgroundMusicVolumn1 = 1;
float g_soundEffectVolumn1 = 1;
#endif

void audioPlayer(const std::string& audioPath, bool isLoop) 
{
	//通过文件夹名来获取audioplayer处理的类型
	std::string audiotype = audioPath.substr(0, audioPath.find('/'));
	if (audiotype == "Music")
	{
		if (g_backgroundMusicSign1 != cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID)
		{
			cocos2d::experimental::AudioEngine::stop(g_backgroundMusicSign1);
		}
		if (g_backgroundMusicVolumn1 != 0) 
		{
			int musicID = cocos2d::experimental::AudioEngine::play2d(audioPath, isLoop, g_backgroundMusicVolumn1);
			if (musicID != cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID)
			{
				g_backgroundMusicSign1 = musicID;
			}
		}
	}
	else if (audiotype == "Sound")
	{
		int soundID = cocos2d::experimental::AudioEngine::play2d(audioPath, false, g_soundEffectVolumn1);
		if (soundID != cocos2d::experimental::AudioEngine::INVALID_AUDIO_ID)
		{
			g_soundEffectSign1 = soundID;
		}
	}
}