/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Player.cpp
 * File Function: Player类的实现
 * Author:        张翔、上官思杨、李昊
 * Update Date:   2024/12/5
 ****************************************************************/

#include "Player.h"

USING_NS_CC;

// 静态实例初始化
Player* Player::_instance = nullptr;

// 获取单例实例
Player* Player::getInstance() 
{
    if (_instance == nullptr) {
        // 使用 no-throw 分配内存
        _instance = new (std::nothrow) Player(); 
        // 初始化失败则销毁实例
        if (_instance && !_instance->init()) {   
            CC_SAFE_DELETE(_instance);
        }
    }
    return _instance;
}

// 构造函数
Player::Player() : _direction(Vec2::ZERO), _keyboardListener(nullptr) , _speed(NOMAL_PLAYER_SPEED){}

// 析构函数
Player::~Player()
{
    if (_keyboardListener) {
        // 检查监听器是否还在事件调度器中
        _eventDispatcher->removeEventListener(_keyboardListener);
        _keyboardListener = nullptr; // 避免悬空指针
    }
    // 调用父类的析构函数以释放 Sprite 资源
    Sprite::~Sprite();
}

// 初始化
bool Player::init() 
{
    if (!Sprite::init()) {
        return false;
    }

    // 加载玩家纹理
    if (!this->initWithFile("Dwarf.png")) {
        CCLOG("Failed to load player sprite");
        return false;
    }

    setPlayerFrame();

    // 注册 update
    this->scheduleUpdate();

    // 注册键盘监听器
    registerKeyboardListener();

    return true;
}

// 设置方向
void Player::setDirection(const Vec2& direction) 
{
    // 保证方向向量归一化
    _direction = direction.getNormalized(); 
}

// 获取方向
Vec2 Player::getDirection() const 
{
    return _direction;
}

// 设置速度
void Player::setSpeed(const float speed)
{
    _speed = speed;
}

// 获取速度
float Player::getSpeed() const
{
    return _speed;
}

// 每帧更新
void Player::update(float delta) 
{
    // 调用sprite的update函数同步更新
    Sprite::update(delta);

    // 获取玩家位置
    _position = Sprite::getPosition();
    // 移动玩家位置
    if (_direction != Vec2::ZERO) 
    {
        setSpeed(5);
        this->setPosition(_position.x + _direction.x * _speed, _position.y + _direction.y * _speed);
        _position.x += _direction.x * _speed;
        _position.y += _direction.y * _speed;
        setSpeed(0);
    }
    updateFrame(delta);

}

void Player::registerKeyboardListener()
{
    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_W: 
                _direction.y = 1;
                break;
            case EventKeyboard::KeyCode::KEY_S:
                _direction.y = -1; 
                break;
            case EventKeyboard::KeyCode::KEY_A: 
                _direction.x = -1; 
                break;
            case EventKeyboard::KeyCode::KEY_D: 
                _direction.x = 1;
                break;
            default: 
                break;
        }
        };

    eventListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_W: 
                if (_direction.y == 1) 
                    _direction.y = 0;
                break;
            case EventKeyboard::KeyCode::KEY_S: 
                if (_direction.y == -1) 
                    _direction.y = 0;
                break;
            case EventKeyboard::KeyCode::KEY_A:
                if (_direction.x == -1) 
                    _direction.x = 0;
                break;
            case EventKeyboard::KeyCode::KEY_D: 
                if (_direction.x == 1) 
                    _direction.x = 0;
                break;
            default: 
                break;
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

// 销毁实例
void Player::destroyInstance() 
{
    CC_SAFE_DELETE(_instance);
}

void Player::setPlayerFrame()
{
    auto tex = Director::getInstance()->getTextureCache()->addImage("Player.png");
    SpriteFrame* tframe;
    for (int i = 0; i < 4; i++)
    {
        auto tname = new char[10];
        for (int j = 0; j < 4; j++) 
        {
            sprintf(tname, "role_%d", i * 4 + j + 1);
            tframe = SpriteFrame::createWithTexture(tex, Rect(32 * j, 48 * i, 32, 48));
            SpriteFrameCache::getInstance()->addSpriteFrame(tframe, tname);
        }
    }
    Sprite::initWithSpriteFrameName("role_1");
}

void Player::updateFrame(float delta)
{
    int _framebasic;
    if (_direction == Vec2(1, 0))
        _framebasic = 9;
    else if (_direction == Vec2(-1, 0))
        _framebasic = 5;
    else if (_direction == Vec2(0, 1))
        _framebasic = 13;
    else
        _framebasic = 1;

    if (_currentFrame < _framebasic || _currentFrame >= _framebasic + 4)
        _currentFrame = _framebasic;

    if (_direction != Vec2::ZERO) 
    {
        _timelast += delta;
        if (_timelast > 0.1f)
        {
            _timelast -= 0.1f;
            ++_currentFrame;
            if (_currentFrame > 3 + _framebasic)
            {
                _currentFrame = _framebasic;
            }
            char* texName = new char[10];
            sprintf(texName, "role_%d", _currentFrame);
            setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(texName));
            delete texName;
        }
    }
    else 
    {
        _timelast = 0;
    }
}