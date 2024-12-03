#include "Player.h"

USING_NS_CC;

Player::Player() : speed(300.0f) {}

Player::~Player() {}

Player* Player::create(const std::string name, const std::string spriteFile)
{
    Player* ret = new Player();
    if (ret && ret->initWithFile("../Resources/test.png")) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

void Player::move(float dx, float dy)
{
    this->setPosition(this->getPosition() + Vec2(dx * speed, dy * speed));
}
