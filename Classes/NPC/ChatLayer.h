#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

// 继承自LayerColor 以让背景变灰
class ChatLayer : public LayerColor {
public:
	ChatLayer();
	~ChatLayer();

	virtual bool init();
	CREATE_FUNC(ChatLayer);
	static ChatLayer* create(const char* backgroundImage, Size dialogSize);

	// 触摸事件监听
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	// 标题
	void setTitle(std::string title, int fontsize = 20);
	// 文本
	void setContentText(std::string text, int fontsize = 20, int padding = 50, int paddintTop = 100);
	// 设置回调函数
	void setCallbackFunc(Ref* target, SEL_CallFuncN callfun);
	// 添加button 用于玩家回复
	bool addButton(const char* normalImage, const char* selectedImage, std::string title, int tag = 0);
	
	// 设置对话框
	void setauto(std::string _title,std::string _content,std::string buttonword);

	virtual void onEnter();
	virtual void onExit();
	// 设置各元素位置 自动调用
	void backgroundFinish();

private:

	void buttonCallBack(Ref* pSender);

	// 文字内容两边的空白区
	int m_contentPadding;
	int m_contentPaddingTop;

	Size m_dialogContentSize;

	Ref* m_callbackListener;
	SEL_CallFuncN m_callback;

	// 自动为成员变量设置setXX和getXX的方法
	CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
	CC_SYNTHESIZE_RETAIN(Sprite*, m__sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m__s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltContentText, LabelContentText);
};
