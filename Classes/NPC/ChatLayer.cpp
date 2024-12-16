#include "ChatLayer.h"

USING_NS_CC;

ChatLayer::ChatLayer() :m__pMenu(NULL), m_contentPadding(0), m_contentPaddingTop(0), m_callbackListener(NULL), m_callback(NULL), m__sfBackGround(NULL), m__s9BackGround(NULL), m__ltContentText(NULL), m__ltTitle(NULL){}

ChatLayer::~ChatLayer() 
{
	CC_SAFE_RELEASE(m__pMenu);
	CC_SAFE_RELEASE(m__sfBackGround);
	CC_SAFE_RELEASE(m__ltContentText);
	CC_SAFE_RELEASE(m__ltTitle);
	CC_SAFE_RELEASE(m__s9BackGround);
}

bool ChatLayer::init() 
{
	if (!LayerColor::init()) 
	{
		return false;
	}

	// 初始化需要的 Menu
	Menu* menu = Menu::create();
	menu->setPosition(cocos2d::Vec2(0, 0));
	setMenuButton(menu);

	// 添加触摸事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ChatLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ChatLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ChatLayer::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	setColor(ccc3(0, 0, 0));
	setOpacity(128);

	return true;
}
// 触摸事件监听
bool ChatLayer::onTouchBegan(Touch* touch, Event* event) 
{
	return true;
}
// 触摸事件监听
void ChatLayer::onTouchMoved(Touch* touch, Event* event) 
{

}
// 触摸事件监听
void ChatLayer::onTouchEnded(Touch* touch, Event* event) 
{

}

ChatLayer* ChatLayer::create(const char* backgroundImage, Size dialogSize)
{

	ChatLayer* layer = ChatLayer::create();

	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));

	layer->m_dialogContentSize = dialogSize;

	return layer;
}
// 标题
void ChatLayer::setTitle(std::string title, int fontsize ) 
{
	LabelTTF* label = LabelTTF::create(title, "", fontsize);
	setLabelTitle(label);
}
// 文本
void ChatLayer::setContentText(std::string text, int fontsize, int padding, int paddingTop) 
{
	LabelTTF* ltf = LabelTTF::create(text, "", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}
// 保存回调函数
void ChatLayer::setCallbackFunc(Ref* target, SEL_CallFuncN callfun) 
{
	m_callbackListener = target;
	m_callback = callfun;
}
// 添加button
bool ChatLayer::addButton(const char* normalImage, const char* selectedImage, std::string title, int tag) 
{
	auto size = Director::getInstance()->getWinSize();
	auto center = Point(size.width / 2, size.height / 3);

	// 创建图片菜单按钮
	auto item = MenuItemImage::create(normalImage, selectedImage, CC_CALLBACK_1(ChatLayer::buttonCallBack, this));
	item->setTag(tag);
	item->setPosition(center);

	// 添加文字说明并设置位置
	Size itemSize = item->getContentSize();
	LabelTTF* ttf = LabelTTF::create(title, "", 20);
	ttf->setColor(Color3B(0, 0, 0));
	ttf->setPosition(Point(itemSize.width / 2, itemSize.height / 3));
	item->addChild(ttf);

	getMenuButton()->addChild(item);

	return true;
}
// 设置button的默认回调函数
void ChatLayer::buttonCallBack(Ref* pSender) 
{
	Node* node = dynamic_cast<Node*>(pSender);
	if (m_callback && m_callbackListener) {
		(m_callbackListener->*m_callback)(node);
	}
	// 退出该对话框
	this->removeFromParent();
}

void ChatLayer::onEnter() 
{
	LayerColor::onEnter();

	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Point(winSize.width / 2, winSize.height / 3);

	//添加背景图片
	Scale9Sprite* background = getSprite9BackGround();
	background->setContentSize(m_dialogContentSize);
	background->setPosition(Point(winSize.width / 2, winSize.height / 3));
	this->addChild(background, 0, 0);

	// 弹出效果
	Action* ChatLayer = Sequence::create(
		ScaleTo::create(0.0, 0.0),
		ScaleTo::create(0.2, 1.05),
		ScaleTo::create(0.2, 0.95),
		ScaleTo::create(0.1, 1.0),
		CallFunc::create(CC_CALLBACK_0(ChatLayer::backgroundFinish, this)),
		NULL
	);
	background->runAction(ChatLayer);
}
// 设置各元素位置 自动调用
void ChatLayer::backgroundFinish()
{
	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Point(winSize.width / 3, winSize.height / 3);

	// 添加按钮，并设置其位置
	this->addChild(getMenuButton());
	float btnWidth = m_dialogContentSize.width / (getMenuButton()->getChildrenCount() + 1);

	Vector<Node*> vector = getMenuButton()->getChildren();
	Ref* pObj = NULL;
	int i = 0;
	for (Node* pObj : vector) 
	{
		Node* node = dynamic_cast<Node*>(pObj);
		node->setPosition(Point(winSize.width / 2 - m_dialogContentSize.width / 2 + btnWidth * (i + 1), winSize.height / 3 - m_dialogContentSize.height / 3));
		i++;
	}

	// 显示对话框标题
	if (getLabelTitle()) 
	{
		getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, m_dialogContentSize.height / 2 - 35.0f)));
		this->addChild(getLabelTitle());
	}

	// 显示文本内容
	if (getLabelContentText()) 
	{
		CCLabelTTF* ltf = getLabelContentText();
		ltf->setPosition(ccp(winSize.width / 2, winSize.height / 3));
		ltf->setDimensions(CCSizeMake(m_dialogContentSize.width - m_contentPadding * 2, m_dialogContentSize.height - m_contentPaddingTop));
		ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
		this->addChild(ltf);
	}
}

void ChatLayer::onExit() 
{
	LayerColor::onExit();
}
// 整体设置对话框
void ChatLayer::setauto(std::string _title, std::string _content,std::string buttonword)
{
	// 设置标题
	this->setTitle(_title, 24);
	// 设置内容文本
	this->setContentText(_content, 20, 50, 100);
	// 添加按钮
	this->addButton("close.png", "close.png", buttonword);
}