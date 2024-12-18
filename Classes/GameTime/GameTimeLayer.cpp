#include "GameTimeLayer.h"
#include "../proj.win32/Constant.h"
USING_NS_CC;

GameTimeLayer* GameTimeLayer::instance = nullptr;

GameTimeLayer::GameTimeLayer()
{
}

GameTimeLayer* GameTimeLayer::getInstance()
{
	if (instance == nullptr) {
		// ʹ�� nothrow �����ڴ�
		instance = new (std::nothrow) GameTimeLayer();
		// ��ʼ��ʧ��������ʵ��
		if (!instance) {
			CC_SAFE_DELETE(instance);
		}
	}
	return instance;
}

void GameTimeLayer::GameTimeLayerUpdate(Camera* camera) 
{
	// ����ʱ����ʾ
	clean("timelabel");
	gametime = GameTime::getInstance();
	timeLabel = Label::createWithSystemFont(gametime->toString(), "Arial", 30);
	float cameraWidth = Director::getInstance()->getVisibleSize().width * (camera->getPosition3D().z / DEFAULT_VIEW_HEIGHT);
	float cameraHeight = Director::getInstance()->getVisibleSize().height * (camera->getPosition3D().z / DEFAULT_VIEW_HEIGHT);
	timeLabel->setPosition(camera->getPosition() + Vec2(240, 180) * (camera->getPosition3D().z / DEFAULT_VIEW_HEIGHT));
	this->addChild(timeLabel, 10, "timelabel");
	timeLabel->setCameraMask(unsigned short(CameraFlag::USER1));

	// ���ʱ����ʾ�ı���
	clean("layercolor");
	layercolor = LayerColor::create(Color4B(0, 255, 0, 128));
	layercolor->setContentSize(Size(timeLabel->getContentSize().width, timeLabel->getContentSize().height + 5));
	layercolor->setAnchorPoint(Vec2(0, 0));
	layercolor->setPosition(timeLabel->getPosition() - timeLabel->getContentSize() / 2);
	this->addChild(layercolor, 8, "layercolor");
	layercolor->setCameraMask(unsigned short(CameraFlag::USER1));
	// ���ʱ����ʾ�����
	clean("sprite");
	sprite = Sprite::create("chatBox.png");
	sprite->setContentSize(layercolor->getContentSize());
	sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setPosition(timeLabel->getPosition() - timeLabel->getContentSize() / 2);
	this->addChild(sprite, 9, "sprite");
	sprite->setCameraMask(unsigned short(CameraFlag::USER1));
}

void GameTimeLayer::clean(std::string name) 
{
	auto removelabel = this->getChildByName(name);
	if (removelabel != nullptr)
	{
		removelabel->removeFromParentAndCleanup(true);
	}
}